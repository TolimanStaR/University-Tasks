#!/bin/bash

set -o noglob


numbers=(
	"zero"    0    "ноль"     0     "целковый"       1
	"one"     1    "один"     1     "полушка"        2
	"two"     2    "два"      2     "четвертушка"    3
	"three"   3    "три"      3     "осьмушка"       4
	"four"    4    "четыре"   4     "пудовичок"      5
	"five"    5    "пять"     5     "медячок"        6
	"six"     6    "шесть"    6     "серебрячок"     7
	"seven"   7    "семь"     7     "золотничок"     8
	"eight"   8    "восемь"   8     "девятичок"      9
	"nine"    9    "девять"   9     "десятичок"      10
)

operations=(  
	"plus"           +    "плюс"          +    "прибавить"    +
	"addition"       +    "сложить"       +
	"minus"          -    "минус"         -
	"substraction"   -    "вычитание"     -
	"multiple"       *    "умножение"     *
	"factor"         *    "множить"       *
	"divide"         /    "деление"       /
	"segmentation"   /    "разделить"     /    "поделить"     /      "дели"    /
)

empty_states=(
	"in" "with" "at" "and" "by" "then"
	"в"  "c"    "на"   "да"   "и" "к"  "нему"  "этому" "ка"  "а"
	"дружок"  "пожалуйста"  "ну"  "мне"  "еще"  "потом"  "затем"
)

raw_operations=(
	+
	-
	*
	/
)


coefficient=100


# params:
# $1 - first     ->   just a number from range [0, (len(target)+1)*(len(pattern)+1)]
# $2 - second    ->   the same with first parameter
function max () { # -> returns a maximal value from two given

	first=$1
	second=$2

	if [[ $first -ge $second ]]; then
		return $first
	else
		return $second
	fi

}


# params:
# $1 - first_string
# $2 - second_string
function compare_strings () { # -> returns 1 if strings are equal else 0
	equal=0
	
	first_string=$1
	second_string=$2

	first_length=${#first_string}
	second_length=${#second_string}

	if [[ "$first_length" -ne "$second_length" ]]; then
		equal=0
	else
		eq_counter=0
		for (( pos = 0; pos < $first_length; pos++ )); do
			if [[ "${first_string:pos:1}" = "${second_string:pos:1}" ]]; then
				eq_counter=$(($eq_counter+1))
			fi
		done
		if [[ "$eq_counter" -eq "$first_length" ]]; then
			equal=1
		else
			equal=0
		fi
	fi

	return $equal
}


function empty_state () {
	return 0
}


function Exception () {
	echo -e "\033[91m"
	printf 'К сожалению, сэр, я не могу распознать это выражение\n'
	echo -e "\033[00m"
	exit -1
}


# params:
# $1 - target     ->   statement which coincidence with pattern it have to find 
# $2 - pattern    ->   just statement from list of correct ones
function get_pattern_coincidence () # -> returns a number from [0, 100] which tells us about 
									# -> the similaryty with every statement from given list
{ 
	current_coincidence=0

	target=$1
	pattern=$2

	target_length=${#target}
	pattern_length=${#pattern}
	table_length=$((($target_length+1)*($pattern_length+1)))

	table=(0)

	for (( i = 0; i < $table_length; i++ )); do
		table+=(0)
	done


	for (( i = 0; i < $target_length; i++ )); do
		for (( j = 0; j < $pattern_length; j++ )); do

			current_dynamic_index=$((($i+1)*$pattern_length+$j+1))
			diag_prev_dynamic_index=$(($i*$pattern_length+$j))
			left_dynamic_index=$((($i+1)*$pattern_length+$j))
			upper_dynamic_index=$(($i*$pattern_length+$j+1))

			if [[ "${target:i:1}" = "${pattern:j:1}" ]]; then
				let table[$current_dynamic_index]=$((${table[$diag_prev_dynamic_index]}+1))
			else
				max ${table[$left_dynamic_index]} ${table[$upper_dynamic_index]}
				let table[$current_dynamic_index]=$?
			fi

		done
	done

	for (( ind = 0; ind < $table_length; ind++ )); do

		if [[ ${table[$ind]} -ge "$current_coincidence" ]]; then
			let current_coincidence=${table[$ind]}
		fi

	done

	return $((($current_coincidence*$coefficient)/$target_length))
}



# params:
# $1 - statement   ->   what it have to recognize
# $2 - list        ->   array of correct statements
function get_most_similar () # -> returns a expression (number or binary operation)
{
	coincidence=0

	list=("$@")
	list_length=$((${#list[@]}/2))
	statement=$1

	most_similar=0
	current=0

	for (( index = 1; index < $(($list_length+1)); index++ )); do

		get_pattern_coincidence $statement ${list[$(($index*2-1))]}
		coincidence=$?

		if [[ "$coincidence" -gt "$current" ]]; then
			current=$coincidence
			most_similar=$((($index-1)*2+1))
		fi
	done
	

	return $most_similar
} 

# params:
# $1 - request_statement     -> just number or operator or string
function type_id () {   # -> returns type of statement: 
						# - 0   ->    raw number     
						# - 1	->    raw binop
						# - 2	->    number statement (string)
						# - 3   ->    binop statement  (string)
						# - 4   ->    empty statement  (string)
						#
						# - 255 (-1)   ->   undefined statement (string)

	request_statement=$1

	typeid=-1
	included=0

	number_basics=( 0 1 2 3 4 5 6 7 8 9 )
	binop_basics=( + - * / )

	# Check for raw number:

	for (( i1 = 0; i1 < ${#number_basics[@]}; i1++ )); do
		if [[ "${number_basics[i1]}" = "$request_statement" ]]; then
			return 0
		fi
	done

	# Check for raw binop:

	for (( i2 = 0; i2 < ${#binop_basics[@]}; i2++ )); do
		if [[ "${binop_basics[i2]}" = "$request_statement" ]]; then
			return 1
		fi
	done

	for (( ie = 0; ie < ${#empty_states[@]}; ie++ )); do
		compare_strings $request_statement ${empty_states[$ie]}
		result=$?
		if [[ "$result" -eq 1 ]]; then
			return 4
		fi
	done

	number_c=0
	binop_c=0

	cur_number_c=0
	cur_binop_c=0

	current_number_index=1
	current_op_index=1

	for (( ic = 0; ic < $((${#numbers[@]}/2)); ic++ )); do
		get_pattern_coincidence $request_statement ${numbers[$(($ic*2))]}
		cur_number_c=$?

		if [[ "$cur_number_c" -gt "$number_c" ]]; then
			number_c=$cur_number_c
			current_number_index=$(($ic*2+1))
		fi
	done

	for (( ib = 0; ib < $((${#operations[@]}/2)); ib++ )); do
		get_pattern_coincidence $request_statement ${operations[$(($ib*2))]}
		cur_binop_c=$?
		if [[ "$cur_binop_c" -gt "$binop_c" ]]; then
			binop_c=$cur_binop_c
			current_op_index=$(($ib*2+1))
		fi
	done

	active_sum=$(($number_c+$binop_c))

	# echo $number_c
	# echo $binop_c

	if [[ "$active_sum" -gt 0 ]]; then
		if [[ "$number_c" -gt "$binop_c" ]]; then
			return 2
		else
			return 3
		fi
	fi

	return $typeid
}


# params:
# $1 - result of the expression (number)
# $2 - string of the expression
function show_result () {
	printf '\nЕсли я правильно понял, вы имели ввиду выражение \"%s\"\n\nРезультат его выполнения : %s\n\n' $2 $1
}


function basic_mode () { # Simple version that solves expressions like "X + Y"

	expression=("$@")

	left_statement=${expression[0]}
	binary_operation=${expression[1]}
	right_statement=${expression[2]}

	get_most_similar $left_statement "${numbers[@]}"
	result=$?
	left=${numbers[$result]}

	get_most_similar $binary_operation "${operations[@]}"
	result=$?
	operator=${operations[result]}

	get_most_similar $right_statement "${numbers[@]}"
	result=$?
	rightn=${numbers[$result]}

	simple_expression=$left$operator$rightn

	show_result $(($left$operator$rightn)) $simple_expression

}

function advanced_mode () { # Распознает любое корректное выражение, написанное хоть на двух языках и третьей рукой
							# Требуется доработка - пристроить сюда ИИ, пусть мучается блин

	printf "\nЯ вас понял. Секунду, я думаю, что это могло бы значить...\n"

	adv_expression=("$@")

	expression_length=$((${#adv_expression[@]}))

	# echo $expression_length

	final_expr=""
	condition=0  # 0 - number, 1 - binop  (Current condition of expression parsing)

	for (( stat = 0; stat < $expression_length; stat++ )); do
		type_id ${adv_expression[$stat]}
		type=$?

		res_statement=""

		if [[ "$type" -eq 4 ]]; then
			continue
		elif [[ "$type" -eq -1 ]]; then
			continue
		elif [[ "$type" -eq 0 || "$type" -eq 1 ]]; then
			if [[ "$condition" -eq "$type" ]]; then
				let condition=$(($condition^1))  # Change the current condition to check next statement from expression
				res_statement=${adv_expression[$stat]}
			else
				Exception
			fi
		elif [[ "$type" -eq 2 ]]; then
			if [[ "$condition" -eq 0 ]]; then
				let condition=$(($condition^1))
				get_most_similar ${adv_expression[$stat]} "${numbers[@]}"
				r_index=$?
				res_statement=${numbers[$r_index]}
			else
				Exception
			fi
		elif [[ "$type" -eq 3 ]]; then
			if [[ "$condition" -eq 1 ]]; then
				let condition=$(($condition^1))
				get_most_similar ${adv_expression[$stat]} "${operations[@]}"
				r_index=$?
				res_statement=${operations[$r_index]}
			else
				Exception
			fi
		fi

		# более дурацкая реализация без состояний
		#
		# case "$type" in
		# 	0 )
		# 		res_statement=${adv_expression[$stat]}
		# 		;;
		# 	1 )
		# 		res_statement=${adv_expression[$stat]}
		# 		;;
		# 	2 )
		# 		get_most_similar ${adv_expression[$stat]} "${numbers[@]}"
		# 		r_index=$?
		# 		res_statement=${numbers[$r_index]}
		# 		;;
		# 	3 )
		# 		get_most_similar ${adv_expression[$stat]} "${operations[@]}"
		# 		r_index=$?
		# 		res_statement=${operations[$r_index]}
		# 		;;
		# 	4 )  continue ;;
		# 	-1 ) continue ;; 
		# esac

		final_expr+="$res_statement"

		# echo $res_statement
	done

	# echo $final_expr
	# echo $(($final_expr))

	show_result $(($final_expr)) $final_expr
}


function main ()
{

	printf '\nРад приветствовать, %s\n\nВведите выражение, которое вы хотели бы распознать: \n' `whoami`
	echo -e "\033[92m"
	read -a expression
	echo -e "\033[00m"

	if [[ "$1" = "-a" ]]; then
		advanced_mode "${expression[@]}"
	else
		basic_mode "${expression[@]}"
	fi

}


args=("$@")
main "${args[@]}"
