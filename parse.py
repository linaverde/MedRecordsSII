import os
import argparse
import json


def get_recursively(search_dict, field, value):
    if isinstance(search_dict, dict):
        if field in search_dict and search_dict[field] == value:
            return search_dict
        for key in search_dict:
            item = get_recursively(search_dict[key], field, value)
            if item is not None:
                return item
    elif isinstance(search_dict, list):
        for element in search_dict:
            item = get_recursively(element, field, value)
            if item is not None:
                return item
    return None


name_ignore_set = {}

meta_ignore_set = {
    "Составной признак",
    "Тип возможных значений",
    "Качественные значения",
    "Интегрирующее значение"
}

separator_by_meta = {
    "Характеристика" : "   =>   "
}

def get_separator_by_meta(meta):
    separator = separator_by_meta.get(meta)
    if separator == None:
        separator = "::"
    return separator

def improved_parse(complaints):
    result = []
    for c in complaints:
        name = c.get("name")
        meta = c.get("meta")
        if name == None or meta == None:
            continue

        if meta == "Значение":
            result.append(name)

        else:
            successors = c.get("successors")
            if successors != None:
                recursive = improved_parse(successors)
                for r in recursive:
                    prefix = ""
                    if name not in name_ignore_set and meta not in meta_ignore_set:
                        prefix = name + get_separator_by_meta(meta)
                    result.append(prefix + r)

    return result


def parse(arg_complaints):
    complaints = get_recursively(arg_complaints, "name", "Жалобы")

    result = improved_parse(complaints["successors"])
    return result


if __name__ == "__main__":
    # arg_parser = argparse.ArgumentParser(allow_abbrev=False)

    # arg_parser.add_argument(
    #     '-i', '--input',
    #     dest='input',
    #     required=True,
    #     type=str,
    #     help="path to the json file to parse"
    # )

    # args = arg_parser.parse_args()

    # input_dir = os.path.dirname(args.input)
    # if input_dir != "" and not os.path.isdir(input_dir):
    #     print('Directory \"{}\" doesn\'t exist'.format(input_dir))
    #     exit(-1)

    finput = "./complaints.json"

    with open(finput, "r", encoding="UTF-8") as f:
        complaints = json.load(f)

    results = parse(complaints)

    with open(r'parsed.txt', 'w') as fp:
        for item in results:
            fp.write("%s\n" % item)
        print('Done')
