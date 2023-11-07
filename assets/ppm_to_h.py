import argparse
import os


def convert_to_h(file_name, destination_folder):
    name_start = 0
    if '/' in file_name:
        name_start = file_name.rindex('/') + 1
    elif '\\' in file_name:
        name_start = file_name.rindex('\\') + 1

    name = file_name[name_start:-4]
    output_path = destination_folder + name + ".h"

    with open(file_name, "r") as file:
        with open(output_path, "w") as output:
            starting_line = f"int {name}[] =\n"
            starting_line += "{\n"
            output.write(starting_line)
            num = 0
            for line in file.readlines():
                if num > 3:
                    output.write(line[:-1] + ",\n")
                num += 1
            output.write("};")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog='PPM to H converter',
        description='Converts a .ppm file to an array in a .h file'
    )

    parser.add_argument('-f', '--file')
    parser.add_argument('-d', '--destination')
    args = parser.parse_args()
    if not args.destination:
        args.destination = os.curdir

    if args.file[-4:] != '.ppm':
        print("ERROR: Need to input a .ppm file to run this script.")
        exit(0)
    elif args.file[-4:] == '.ppm':
        print(f"Converting {args.file} into a .h file")
        convert_to_h(args.file, args.destination)
        output_file = args.file[:-4] + ".h"
        print(f"Conversion complete. Check {output_file} for the output")
    else:
        print("ERROR: File needed to run this script")
        exit(0)
