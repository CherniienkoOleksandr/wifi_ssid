_myutil() {
	local cur="${COMP_WORDS[COMP_CWORD]}"
	local prev="${COMP_WORDS[COMP_CWORD - 1]}"

	case "$prev" in
	-s | --switch)
		COMPREPLY=($(compgen -W "$(myutil --list-switches)" -- "$cur"))
		return
		;;
	esac

	COMPREPLY=($(compgen -W "-h --help -p --print -s --switch" -- "$cur"))
}

complete -F _myutil myutil
