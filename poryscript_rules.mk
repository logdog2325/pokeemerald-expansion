# Poryscript (.pory -> .inc) rules for Draconid Emerald.
#
# Every *.pory file under data/ is compiled to the .inc file next to it. The
# generated .inc files are committed so the ROM still builds on a machine
# without Poryscript; when the binary is missing and a .pory is newer than its
# .inc, the build stops with a hint instead of silently using a stale script.
# Install the tool with: tools/hack/install_tools.sh

PORYSCRIPT_DIR := $(TOOLS_DIR)/poryscript
PORYSCRIPT     := $(PORYSCRIPT_DIR)/poryscript$(EXE)
PORYSCRIPT_ARGS := -fc $(PORYSCRIPT_DIR)/font_config.json -cc $(PORYSCRIPT_DIR)/command_config.json -lm=false

PORY_SRCS := $(shell find $(DATA_ASM_SUBDIR) -type f -name '*.pory')
PORY_INCS := $(PORY_SRCS:.pory=.inc)

AUTO_GEN_TARGETS += $(PORY_INCS)

$(DATA_ASM_SUBDIR)/%.inc: $(DATA_ASM_SUBDIR)/%.pory $(PORYSCRIPT_DIR)/font_config.json $(PORYSCRIPT_DIR)/command_config.json
	@if [ -x "$(PORYSCRIPT)" ]; then \
		echo "$(PORYSCRIPT) -i $< -o $@"; \
		$(PORYSCRIPT) -i $< -o $@ $(PORYSCRIPT_ARGS); \
	else \
		echo "error: $< is newer than $@ but $(PORYSCRIPT) is not installed."; \
		echo "       Run tools/hack/install_tools.sh (or install Poryscript) and rebuild."; \
		exit 1; \
	fi
