#!/bin/bash -x

if (($# == 2));
then
        cat $1 > $2
else
        echo "Wrong parameters format!"
fi

