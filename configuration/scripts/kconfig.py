import argparse
import os

# Doesn't use tristate symbols. They're supported here just to make the
# script a bit more generic.
from kconfiglib import Kconfig, split_expr, expr_value, expr_str, BOOL, \
                       TRISTATE, TRI_TO_STR, AND, OR
def main():
    args = parse_args()
    kconf = Kconfig(args.kconfig_file, warn_to_stderr=False,
                    suppress_traceback=True)
    # Load configuration files
    kconf.load_config(args.configs_in[0])
    for config in args.configs_in[1:]:
        # replace=False creates a merged configuration
        kconf.load_config(config, replace=False)
    # Write the merged configuration and the C header
    kconf.write_config(os.devnull)
    kconf.write_autoconf(args.header_out)

def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("kconfig_file",
                        help="Top-level Kconfig file")
    parser.add_argument("header_out",
                        help="Output header file")
    parser.add_argument("configs_in",
                        nargs="+",
                        help="Input configuration fragments. Will be merged "
                             "together.")
    return parser.parse_args()

if __name__ == "__main__":
    main()
