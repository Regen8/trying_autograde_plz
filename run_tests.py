#! /usr/bin/env python3

from collections import namedtuple
from typing import List, Tuple, Dict
from os import popen
import os
import subprocess
from sys import argv
from time import time
import json

def unexpected_end_of_input(filename: str, index: int, line: str) -> Exception:
    # filename lineno offset text
    return SyntaxError('unexpected end of input', (filename, index, len(line), line))

def goto_next_line(index: int, lines: List[str], filename: str) -> Tuple[int, str]:
    index += 1
    if index >= len(lines):
        raise unexpected_end_of_input(filename, index, line)
    line = lines[index].strip()
    
    # skip blank lines
    index,line = skip_blank_lines(index, line, lines, filename)
            
    return index,line

def skip_blank_lines(index: int, line: str, lines: List[str], filename: str) -> Tuple[int,str]:
    while not line:
        index,line = goto_next_line(index, lines, filename)
    return index,line

def eat_block_of_code(index, lines, filename) -> Tuple[int,str]:
    # go to next line
    index,line = goto_next_line(index, lines, filename)
    
    # expect start of code block
    if line != '{':
        # filename lineno offset text
        raise SyntaxError('missing expected start of code block: "{"', (filename, index+1, 1, line))
    
    # expect next lines to be unit test code
    open_curly_braces = 1
    while open_curly_braces > 0:
        # go to next line
        index,line = goto_next_line(index, lines, filename)
        
        if line == '{':
            open_curly_braces += 1
        elif line == '}':
            open_curly_braces -= 1
            
    return index,line

def read_tests(filename: str) -> List[Dict[str,str]]:
    tests = list()
    with open(filename) as f:
        lines = f.readlines()
    index = 0
    while index < len(lines):
        line = lines[index].strip()
        
        # skip blank lines
        index,line = skip_blank_lines(index, line, lines, filename)
        
        # expect start of multiline comment
        if line != '/*':
            # filename lineno offset text
            raise SyntaxError('missing expected start of multiline comment: "/*"', (filename, index+1, 1, line))

        # go to next line
        index,line = goto_next_line(index, lines, filename)
        
        # expect next lines to be only attributes and values
        attributes = dict()
        while line.startswith('@'):
            tag,value = line.split(sep=':', maxsplit=1)
            tag = tag.strip()[1:]
            value = value.strip()
            attributes[tag] = value
            
            # go to next line
            index,line = goto_next_line(index, lines, filename)

        # expect end of multiline comment
        if line != '*/':
            # filename lineno offset text
            raise SyntaxError('missing expected end of multiline comment: "*/"', (filename, index+1, 1, line))
        
        # verify all required attributesare present
        required_attributes = ('name', 'points', 'type', 'target', 'number')
        for attribute in required_attributes:
            if attribute not in attributes:
                raise KeyError('missing required attribute: {}'.format(attribute))
        
        
        type = attributes['type'] 
        if type == 'unit':
            # go to next line
            index,line = goto_next_line(index, lines, filename)
            
            # expect start of code block
            if line != '{':
                # filename lineno offset text
                raise SyntaxError('missing expected start of code block: "{"', (filename, index+1, 1, line))
            
            # expect next lines to be unit test code
            open_curly_braces = 1
            code = str()
            while open_curly_braces > 0:
                # go to next line
                index,line = goto_next_line(index, lines, filename)
                
                if line == '{':
                    open_curly_braces += 1
                elif line == '}':
                    open_curly_braces -= 1
                
                if open_curly_braces > 0:
                    code += line + '\n'
                    
            attributes['code'] = code
            tests.append(attributes)
        elif type == 'i/o':
            # go to next line
            index,line = goto_next_line(index, lines, filename)
            if line != '{':
                # filename lineno offset text
                raise SyntaxError('missing expected start of i/o block: "{"', (filename, index+1, 1, line))

            # expect start of code block
            index,line = goto_next_line(index, lines, filename)
            if line != 'input':
                # filename lineno offset text
                raise SyntaxError('missing expected start of i/o block: "input"', (filename, index+1, 1, line))
            
            # go to next line
            index,line = goto_next_line(index, lines, filename)
            input_filename_string = line
            # print("Input filename: " + input_filename_string)

            index,line = goto_next_line(index, lines, filename)
            if line != 'output':
                # filename lineno offset text
                raise SyntaxError('missing expected start of i/o block: "output"', (filename, index+1, 1, line))
            
            index,line = goto_next_line(index, lines, filename)
            output_filename_string = line
            # print("Output filename: " + output_filename_string)

            index,line = goto_next_line(index, lines, filename)
            if line != '}':
                # filename lineno offset text
                raise SyntaxError('missing expected start of i/o block: "}"', (filename, index+1, 1, line))


            with open(input_filename_string, 'r') as f:
                attributes['expected_input'] = f.read()
            with open(output_filename_string, 'r') as f:
                attributes['expected_output'] = f.read()

            tests.append(attributes)

        elif type == 'script':
            # go to next line
            index,line = goto_next_line(index, lines, filename)
            if line != '{':
                # filename lineno offset text
                raise SyntaxError('missing expected start of script block: "{"', (filename, index+1, 1, line))

            # expect start of code block
            index,line = goto_next_line(index, lines, filename)
            if line != 'script':
                # filename lineno offset text
                raise SyntaxError('missing expected start of scriptblock: "input"', (filename, index+1, 1, line))
            
            # go to next line
            index,line = goto_next_line(index, lines, filename)
            script_filename_string = line
            # print("Script filename: " + script_filename_string)

            index,line = goto_next_line(index, lines, filename)
            if line != '}':
                # filename lineno offset text
                raise SyntaxError('missing expected start of script block: "}"', (filename, index+1, 1, line))


            with open(script_filename_string, 'r') as f:
                attributes['script_content'] = f.read()

            tests.append(attributes)

        else:
            #raise ValueError('undefined test type: {}'.format(type))
            print('WARNING: undefined test type: {}.  this one will be ignored: {}'.format(type, attributes['name']))
            index,line = eat_block_of_code(index, lines, filename)
                
        index += 1
    
    return tests

def write_unit_test(test: Dict[str,str]) -> None:
    with open('unit_test.cpp', 'wt') as f:
        f.write('#include "cs12x_test.h"\n')
        f.write('#include "{}"\n\n'.format(test['target']))
        f.write('#include<string>\n')
        f.write('#include<sstream>\n')
        f.write('#include<cstring>\n')

        f.write('int main() {\n')
        f.write('    INIT_TEST;\n')
        f.write('    {}\n'.format('\n    '.join(test['code'].splitlines())))
        f.write('    RESULT(pass);\n')
        f.write('    return pass ? 0 : 1;\n')
        f.write('}\n')

# Writes out the input and output strings
def write_io_test(test: Dict[str,str]) -> None:
    with open('input.txt', 'wt') as f:
        f.write(test['expected_input'])
        f.write("\n")
    with open('output.txt', 'wt') as f:
        f.write(test['expected_output'])

def write_script_test(test: Dict[str,str]) -> None:
    with open('script.sh', 'wt') as f:
        f.write(test['script_content'])

def compile_unit_test() -> bool:
    CXX = 'g++'
    FLAGS = '-std=c++17 -g -o unit_test'
    SRC = 'unit_test.cpp'
    compile_cmd = '{} {} {} 2>&1'.format(CXX, FLAGS, SRC)
    p = popen(compile_cmd)
    try:
        output = p.read()
    except Exception as e:
        output = str(e)
    ret = p.close()
    # print('ret = {}'.format(ret))
    return ret == None, output

def compile_io_test() -> bool:
    CXX = 'g++'
    FLAGS = '-std=c++17 -g -o io_test'
    SRC = 'stress_ball.cpp main.cpp'
    compile_cmd = '{} {} {} 2>&1'.format(CXX, FLAGS, SRC)
    p = popen(compile_cmd)
    try:
        output = p.read()
    except Exception as e:
        output = str(e)
    ret = p.close()
    # print('ret = {}'.format(ret))
    return ret == None, output

def compile_script_test() -> bool:
    return True, ""
    
def run_unit_test() -> bool:
    run_cmd = ["./unit_test", "2>&1"]
    p = subprocess.run(run_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    try:
        output = p.stdout.decode('utf-8')
    except Exception as e:
        output = str(e)
    ret = p.returncode
    # print('ret = {}'.format(ret))
    return ret == 0, output

def run_io_test() -> bool:
    run_cmd = ["./io_test", "2>&1"]
    with open('input.txt', 'r') as file:
        input_data = file.read()
    p = subprocess.Popen(run_cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, err = p.communicate(input_data.encode('utf-8'))
    output_str = output.decode('utf-8').rstrip()
    err_str = err.decode('utf-8')
    # try:
    #     output = p.stdout.decode('utf-8').replace('\r', '')
    # except Exception as e:
    #     output = str(e)
    with open('output.txt', 'r') as file:
        gt_string = file.read().replace('\r', '').rstrip()
    # print('ret = {}'.format(ret))
    # print(output_str)
    message_to_student = "Your output: " + output_str + "\n"
    message_to_student += "\n\n"
    message_to_student += "Expected output: " + gt_string + "\n"
    return (output_str == gt_string), message_to_student

def run_script_test() -> bool:

    print("Can write: ")
    print(os.access('./', os.W_OK))

    cmd = ["bash ./script.sh"]
    #print('cmd = {}'.format(cmd))
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, shell=True)
    # p = popen(cmd)
    output, err = p.communicate()
    # output_str = output.decode('utf-8')
    # err_str = err.decode('utf-8')
    # print(output_str)
    # print(err_str)


    with open('./OUTPUT', 'r') as file:
        output_string = file.read()

    with open('./DEBUG', 'r') as file:
        debug_string = file.read()
        print("Debug: ")
        print(debug_string)
    # try:
    #     output = p.stdout.decode('utf-8')
    # except Exception as e:
    #     output = str(e)

    score = float(output_string)

    return (score > 0.0), debug_string, score

def check_approved_includes(target: str, approved_includes: List[str]) -> bool:
    
    cmd = ["bash"]
    #print('cmd = {}'.format(cmd))
    p = subprocess.Popen(cmd, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    # p = popen(cmd)
    output, err = p.communicate("./approved_includes.sh {} {} 2>&1".format(target, ' '.join(approved_includes)).encode('utf-8'))
    output_str = output.decode('utf-8')
    err_str = err.decode('utf-8')
    # try:
    #     output = p.stdout.decode('utf-8')
    # except Exception as e:
    #     output = str(e)
    forbidden_found = False
    if "FORBIDDEN" in output_str:
        forbidden_found = True
    return forbidden_found, output_str

def main(filename) -> None:
    results = dict()
    test_results = list()
    tests = read_tests(filename)
    earned = 0
    possible = 0
    total_time = 0
    test_num = 1
    results['score'] = 0
    results['output'] = ''
    for test in tests:
        point_multiplier = 100.0
        max_points = float(test['points'])
        possible += max_points
        print('test: {}'.format(test['name']))
        if test['type'] == 'unit':
            write_unit_test(test)
        elif test['type'] == 'i/o':
            write_io_test(test)
        elif test['type'] == 'script':
            write_script_test(test)
        else:
            print("Unsupported test")
            continue
        compile_output, run_output = '',''
        if test['type'] == 'unit':
            compiles, compile_output = compile_unit_test()
        elif test['type'] == 'i/o':
            compiles, compile_output = compile_io_test()
        elif test['type'] == 'script':
            compiles, compile_output = compile_script_test()
        else:
            print("Unsupported test")
            continue
        if compiles:
            time_start = time()
            
            if test['type'] == 'unit':
                runs, run_output = run_unit_test()
            elif test['type'] == 'i/o':
                runs, run_output = run_io_test()
            elif test['type'] == 'script':
                runs, run_output, point_multiplier = run_script_test()
            else:
                print("Unsupported test")
                continue
            time_end = time()
            total_time += time_end - time_start
            
            if runs:
                
                if point_multiplier < 100.0:
                    print("[PASS - PARTIAL] ran correctly, but only recieved {0:2}% partial credit\n".format((point_multiplier)))    
                else:
                    print('[PASS] ran correctly\n')
                points = max_points * (point_multiplier / 100.0)
                earned += points
            else:
                print('[FAIL] incorrect behavior\n')
                points = 0
            
        else:
            print('[FAIL] failed to compile\n')
            print(compile_output)
            points = 0
        
        test_result = dict()
        test_result['score'] = points
        results['score'] += points
        test_result['number'] = str(test['number'])
        test_result['max_score'] = max_points
        test_result['name'] = test['name']
        #test_result['number'] = ''
        test_result['output'] = ''
        if len(compile_output) > 0:
            test_result['output'] += compile_output.strip()
        if len(run_output) > 0:
            if len(compile_output) > 0:
                test_result['output'] += '\n\n'
            test_result['output'] += run_output.strip()
        if test['show_output'] == 'False':
            test_result['output'] = 'Output is intentionally hidden'
        #tags = list()
        #test_result['tags'] = tags
        #test_result['visibility'] = 'hidden'
        #test_result['extra_data'] = dict()
        
        test_results.append(test_result)
    
    targets = set()
    for test in tests:
        targets.add(test['target'])
    
    unapproved_includes = False  
    for target in targets: 
        try:
            f = open('approved_includes_{}'.format(target))
        except FileNotFoundError:
            print('approved_includes_{} not found: assuming default deny all'.format(target))
            continue
        list_of_approved_includes = list()
        for line in f:
            list_of_approved_includes.append(line.strip())
        forbidden_found, output = check_approved_includes(target, list_of_approved_includes)
        test_result = {'score': 2, 'number':'00', 'max_score': 2, 'name': 'Approved includes for {}'.format(target), 'output': output.strip()}
        if (forbidden_found):
            test_result['score'] = 0
            print(test_result['score'])
            unapproved_includes = True
        test_results.append(test_result)
        results['score'] += test_result['score']
        f.close()
    
    if  unapproved_includes:
        results['score'] = 0
    
    # DISABLE SCORING FROM AUTOGRADER
    # results['score'] = 0
    
    results['execution_time'] = total_time
    if unapproved_includes:
        results['output'] = 'Forbidden includes are used, so we set your current submission score to 0.0'
    results['visibility'] = 'visible'
    results['stdout_visibility'] = 'visible'
    # if results['visibility'] == 'visible' or results['stdout_visibility'] == 'visible':
    #     print('###########################')
    #     print('#                         #')
    #     print('# WARNING WARNING WARNING #')
    #     print('#                         #')
    #     if results['visibility'] == 'visible':
    #         print('# TESTS ARE VISIBLE       #')
    #     if results['stdout_visibility'] == 'visible':
    #         print('# STDOUT IS VISIBLE       #')
    #     print('#                         #')
    #     print('###########################')
    #results['extra_data'] = dict()
    results['tests'] = test_results
    #results['leaderboard'] = leaderboard
    
    print('#####################')
    print('                     ')
    print('# points: {:3.0f} / {:3.0f} #'.format(earned,possible))
    print('                     ')
    print('#####################')
    return results
    

if __name__ == '__main__':
    results_filename = 'results.json'
    if len(argv) == 1:
        tests_filename = input('path to tests: ')
    else:
        tests_filename = argv[1]
        if len(argv) > 2:
            results_filename = argv[2]
    results = main(tests_filename)
    #print(json.dumps(results, sort_keys=True, indent=4))
    with open(results_filename,'wt') as f:
        json.dump(results, f, sort_keys=True, indent=4)

    previousMaxScore = 0.0
    with open('/autograder/submission_metadata.json', 'r') as f:
        previousResultJson = json.load(f)
        for prevSubmission in previousResultJson['previous_submissions']:
            previousScore = float(prevSubmission["score"])
            if (previousScore > previousMaxScore):
                previousMaxScore = previousScore

    with open('/autograder/results/results.json', 'r') as f:
        currentResult = json.load(f)

    if (previousMaxScore > float(currentResult['score'])):
        currentResult["output"] +="\n"
        currentResult["output"] += "Your current submission's score was " + str(float(currentResult["score"])) + ", however you get to keep your maximum submission score of " + str(previousMaxScore)
        currentResult['score'] = previousMaxScore

    with open('/autograder/results/results.json', 'w') as f:
        json.dump(currentResult, f)