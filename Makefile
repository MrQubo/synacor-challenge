SHELL = /bin/bash
MV = mv
INTERPRETER = ./arch_interpreter

$(INTERPRETER):
	$(MAKE) -C interpreter build
	$(MV) interpreter/interpreter $(INTERPRETER)

run%: $(INTERPRETER)
	cat <(cut -d"#" -f1 text_game/steps$* | sed "s/[[:space:]]*$$//") - \
	| $(INTERPRETER) challenge.bin

.PHONY: run_text_game
