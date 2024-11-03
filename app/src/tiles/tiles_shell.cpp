#include <zephyr/shell/shell.h>

#include "tiles.h"

extern Tiles tiles;

static int cmd_list_handler(const struct shell *sh, size_t argc, char **argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);

  uint8_t count = tiles.getTilesCount();
  if (count == 0) {
    shell_fprintf(sh, SHELL_ERROR, "No tiles found\n");
    return -ENOEXEC;
  }

  char buff[3];
  Tile *tiles_list = tiles.getTiles();

  buff[3] = '\0';
  shell_fprintf(sh, SHELL_NORMAL, "Tiles:\n");
  for (int i = 0; i < 64; i++) {
    if (tiles_list[i].dev == nullptr) {
      buff[0] = '-';
      buff[1] = '-';
    } else if (tiles_list[i].position.toString(buff) < 2) {
      buff[0] = '?';
      buff[1] = '?';
    }
    shell_fprintf(sh, SHELL_NORMAL,
                  "- Tile %d, pos: %s, color: %x, state: %d\n", i + 1, buff,
                  tiles_list[i].color, tiles_list[i].state ? 1 : 0);
  }

  return 0;
}

static int cmd_get_handler(const struct shell *sh, size_t argc, char **argv) {
  if (argc < 2) {
    shell_fprintf(sh, SHELL_ERROR, "Missing position argument\n");
    return -EINVAL;
  }

  char buff[3];
  ChessPosition position =
      ChessPosition(argv[1][0] - 'a' + 1, argv[1][1] - '1' + 1);

  if (!position.isValid()) {
    shell_fprintf(sh, SHELL_ERROR, "Invalid position\n");
    return -EINVAL;
  }

  position.toString(buff);
  buff[3] = '\0';

  shell_fprintf(sh, SHELL_NORMAL, "Tile position: %s\n", buff);

  Tile *tile = tiles.getTile(position);

  if (tile == nullptr) {
    shell_fprintf(sh, SHELL_ERROR, "Tile not found\n");
    return -ENOEXEC;
  }

  tile->position.toString(buff);

  shell_fprintf(sh, SHELL_NORMAL, "Tile at %s, color: %d, state: %d\n", buff,
                tile->color, tile->state ? 1 : 0);

  return 0;
}

static int cmd_init_handler(const struct shell *sh, size_t argc, char **argv) {
  ARG_UNUSED(argc);
  ARG_UNUSED(argv);

  int ret = tiles.init();
  if (ret < 0) {
    shell_fprintf(sh, SHELL_ERROR, "Failed to initialize tiles\n");
    return ret;
  }

  shell_fprintf(sh, SHELL_NORMAL, "Tiles initialized\n");

  return 0;
}

static int cmd_set_color_handler(const struct shell *sh, size_t argc,
                                 char **argv) {
  if (argc < 3) {
    shell_fprintf(sh, SHELL_ERROR, "Missing position and color arguments\n");
    return -EINVAL;
  }

  ChessPosition position = ChessPosition(argv[1]);
  uint32_t color = strtoul(argv[2], nullptr, 16);

  int ret = tiles.setTileColor(position, color);

  if (ret < 0) {
    shell_fprintf(sh, SHELL_ERROR, "Failed to set tile color\n");
    return ret;
  }

  return 0;
}

static int cmd_set_position_handler(const struct shell *sh, size_t argc,
                                    char **argv) {
  if (argc < 3) {
    shell_fprintf(sh, SHELL_ERROR,
                  "Missing position and new position arguments\n");
    return -EINVAL;
  }

  ChessPosition position = ChessPosition(argv[1]);
  ChessPosition new_position = ChessPosition(argv[2]);

  int ret = tiles.setTilePosition(position, new_position);

  if (ret < 0) {
    shell_fprintf(sh, SHELL_ERROR, "Failed to set tile position\n");
    return ret;
  }

  shell_fprintf(
      sh, SHELL_NORMAL,
      "Current positions are outdated, please run 'tiles init' to update\n");

  return 0;
}

static int cmd_set_threshold_handler(const struct shell *sh, size_t argc,
                                     char **argv) {
  if (argc < 3) {
    shell_fprintf(sh, SHELL_ERROR,
                  "Missing position and threshold arguments\n");
    return -EINVAL;
  }

  ChessPosition position = ChessPosition(argv[1]);
  uint16_t threshold = strtoul(argv[2], nullptr, 10);

  int ret = tiles.setTileThreshold(position, threshold);

  if (ret < 0) {
    shell_fprintf(sh, SHELL_ERROR, "Failed to set tile threshold\n");
    return ret;
  }

  return 0;
}

static int cmd_set_interval_handler(const struct shell *sh, size_t argc,
                                    char **argv) {
  if (argc < 3) {
    shell_fprintf(sh, SHELL_ERROR, "Missing position and interval arguments\n");
    return -EINVAL;
  }

  ChessPosition position = ChessPosition(argv[1]);
  uint16_t interval = strtoul(argv[2], nullptr, 10);

  int ret = tiles.setTileInterval(position, interval);

  if (ret < 0) {
    shell_fprintf(sh, SHELL_ERROR, "Failed to set tile interval\n");
    return ret;
  }

  return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_tiles_set,
    SHELL_CMD(color, NULL, "Set tile color.", cmd_set_color_handler),
    SHELL_CMD(position, NULL, "Set tile position.", cmd_set_position_handler),
    SHELL_CMD(threshold, NULL, "Set tile threshold.",
              cmd_set_threshold_handler),
    SHELL_CMD(interval, NULL, "Set tile interval.", cmd_set_interval_handler),
    SHELL_SUBCMD_SET_END);

SHELL_STATIC_SUBCMD_SET_CREATE(
    sub_tiles, SHELL_CMD(list, NULL, "List all tiles.", cmd_list_handler),
    SHELL_CMD(get, NULL, "Get tile by position.", cmd_get_handler),
    SHELL_CMD(init, NULL, "Initialize tiles.", cmd_init_handler),
    SHELL_CMD(set, &sub_tiles_set, "Set tile properties.", NULL),
    SHELL_SUBCMD_SET_END);

SHELL_CMD_REGISTER(tiles, &sub_tiles, "Tiles controller commands", NULL);
