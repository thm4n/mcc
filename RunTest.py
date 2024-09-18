#!/usr/bin/python3

import argparse
import os
import subprocess
from typing import List, Dict, Any

import tokenizer

MCC_PATH = "./bin/mcc"
TEST_FILES_PATH = "./tests"

def parse_args():
    arg_parser = argparse.ArgumentParser()
    arg_parser.add_argument("-s", "--stage", type=int, default=1, help="stage to check")
    arg_parser.add_argument("-S", "--single-stage", action="store_true", default=False, help="check only the specified stage")
    arg_parser.add_argument("-v", "--valid", action="store_true", default=False, help="test only valid code")
    arg_parser.add_argument("-i", "--invalid", action="store_true", default=False, help="test only invalid code")
    arg_parser.add_argument("--specific", type=str, help="specify specific test from the specified stage")
    args = arg_parser.parse_args()

    if args.valid and args.invalid:
        print("Invalid Arguments Settings: both 'valid' and 'invalid' flags are picked")
        exit(1)
    
    if not args.valid and not args.invalid:
        args.valid = True
        args.invalid = True
    
    return args

def load_test_files(args, test_files_path: str = TEST_FILES_PATH) -> List[Dict[str, Any]]:
    if not os.path.exists(test_files_path):
        err_string = f"no such directory: {test_files_path}"
        print(err_string)
        raise RuntimeError(err_string)
    
    stage_tests = {}
    test_files = []
    tests = {}

    with os.scandir(test_files_path) as entries:
        for entry in entries:
            if not entry.name.startswith('stage_'):
                continue

            stage = int(entry.name[-2:])
            stage_tests[stage] = entry.path

    for stage_num, stage_path in stage_tests.items():
        if args.stage < stage_num:
            continue

        if args.single_stage and args.stage != stage_num:
            continue

        if args.valid:
            with os.scandir(f"{stage_path}/valid") as entries:
                for entry in entries:
                    if not entry.name.endswith('.c'):
                        continue

                    test_files.append({"stage": stage_num, "name": entry.name, "path": entry.path, "valid": True})


        if args.invalid: 
            with os.scandir(f"{stage_path}/invalid") as entries:
                for entry in entries:
                    if not entry.name.endswith('.c'):
                        continue

                    test_files.append({"stage": stage_num, "name": entry.name, "path": entry.path, "valid": False})
   
    return test_files

def perform_test(test_file: Dict[str, Any]) -> bool:
    if not os.path.exists(MCC_PATH):
        raise RuntimeError(f"no such file {MCC_PATH}")
    
    result = subprocess.run([MCC_PATH, test_file['path']], stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    
    stderr = result.stderr
    stdout = result.stdout

    logpath = f"./logs/{test_file['stage']}/"
    logpath += "valid" if test_file['valid'] else "invalid"
    logpath += f"/{test_file['name'][:-2]}"

    os.makedirs(os.path.dirname(logpath), exist_ok=True)

    with open(f"{logpath}.stdout", "w") as fd:
        fd.write(stdout)

    with open(f"{logpath}.stderr", "w") as fd:
        fd.write(stderr)
    
    print(f"\n{stdout}")
    return result.returncode

def main():
    args = parse_args()
    test_files = load_test_files(args)

    stage = 1
    while stage <= args.stage:
        curr_list = [f for f in test_files if(f['stage'] == stage and f['valid'])]
        for test_file in curr_list:
            res = perform_test(test_file)
            print(f"for stage {stage} valid test '{test_file['name']}' : {res}")

        curr_list = [f for f in test_files if(f['stage'] == stage and not f['valid'])]
        for test_file in curr_list:
            res = perform_test(test_file)
            print(f"for stage {stage} invalid test '{test_file['name']}' : {res}")

        stage += 1

if __name__ == "__main__":
    main()
