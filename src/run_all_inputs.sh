#!/bin/bash

printf "organizing example... "
./Organizer --in ./../input_files/example.in --out ./../input_files/example.out > ./../input_files/example.score
printf "Done\n"

printf "organizing me_at_the_zoo... "
./Organizer --in ./../input_files/me_at_the_zoo.in --out ./../input_files/me_at_the_zoo.out > ./../input_files/me_at_the_zoo.score
printf "Done\n"

printf "organizing videos_worth_spreading... "
./Organizer --in ./../input_files/videos_worth_spreading.in --out ./../input_files/videos_worth_spreading.out > ./../input_files/videos_worth_spreading.score
printf "Done\n"

printf "organizing trending_today... "
./Organizer --in ./../input_files/trending_today.in --out ./../input_files/trending_today.out > ./../input_files/trending_today.score
printf "Done\n"

printf "organizing kittens... "
./Organizer --in ./../input_files/kittens.in --out ./../input_files/kittens.out > ./../input_files/kittens.score
printf "Done\n"







