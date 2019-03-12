#!/bin/bash

res_dir=./resources
players_dir="$res_dir/players"

run_bot() {
	map_name=./resources/maps
	echo "$1 vs $2 on map $3"
	run_map "$map_name/$3" "$1" "$players_dir/$2"
	run_map "$map_name/$3" "$players_dir/$2" "$1"
}

run_map() {
	for i in 0 1 2
	do
		"$res_dir"/filler_vm -f "$1" -p1 "$2" -p2 "$3" > out
		error=$(cat out | grep "An error occured. aborting...")
		winner=$(cat filler.trace | grep won)
		echo "$winner"
		if [ ! -z "$error" ];
		then
			mv out error
			exit
		fi
	done
}

test_player() {
	if [[ $2 == "--all" ]]; then
		bots=$(ls $players_dir)
	else
		bots="abanlin.filler champely.filler hcao.filler carli.filler grati.filler superjeannot.filler"
	fi
	for bot in $bots
	do
		run_bot "./emamenko.filler" "$bot" "$1"
	done
}

test_player "$1" "$2"
