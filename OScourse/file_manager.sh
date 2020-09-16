#!/bin/bash


echo 'Добро пожаловать в файловый менеджер'

__name__="$0"


tutorial () {
	echo ''
	echo '--- Информация о скрипте ---'
	echo ''
	echo 'Доступные команды: '
	echo 'help - Увидеть эту страницу'
	echo 'create - Создать файл'
	echo 'modify - Редактировать существующий файл'
	echo 'delete - Удалить файл безвозвратно'
	echo 'list - Список доступных для работы файлов'
	echo ''
}

root () {
	if [ "$1" = "$__name__" ]; then
		echo 'Доступ заблокирован. Введи "hack", чтобы получить доступ'
		read hack
		if [ "$hack" = "hack" ]; then
			echo 'Доступ получен, мой господин'
		else
			echo 'WARNING! Попытка взлома! Вызываю FBI и завершаю работу!'
			exit
		fi
	else
		echo 'Доступ разрешен'
	fi
}


tutorial

while true
do
	read command 
	if [ "$command" = "exit" ]; then
		echo 'Вcё, до свидания! (с) Филипп Киркоров'
		exit
	elif [ "$command" = "help" ]; then
		tutorial
	elif [ "$command" = "create" ]; then
		read new_file
		for file in `ls`
		do
			if [ "$file" = "$new_file" ]; then
				echo 'Файл существует'
			else
				touch "$new_file"
			fi
		done
	elif [ "$command" = "modify" ]; then
		echo 'Выбери файл'
		read file
		root "$file"
		exists="0"
		for f in `ls`
		do
			if [ "$file" = "$f" ]; then
				exists="1"
				break
			fi
		done
		if [ $exists = "0" ]; then
			echo 'Файла не существует. Создать его? yes & no'
			read decision
			if [ "$decision" = "yes" ]; then
				touch $file
			else
				continue
			fi
		fi
		echo 'Выбери режим редактирования - add & rewrite'
		read mode 
		if [ "$mode" = "add" ]; then
			echo 'Введи текст, который нужно дописать в файл'
			read text 
			echo $text >> $file
		elif [ "$mode" = "rewrite" ]; then
			echo 'Введи текст, который нужно записать в файл'
			read text
			echo $text > $file
		else
			echo 'Некорректный режим'
		fi
	elif [ "$command" = "delete" ]; then
		echo 'Введи имя файла, который нужно удалить'
		read file
		root $file
		echo 'Ты точно хочешь удалить файл? yes & no'
		read decision
		if [ "$decision" = "yes" ]; then
			rm $file
		fi
	elif [ "$command" = "list" ]; then
		ls -lsaF
	fi
done
