#!/usr/bin/python3
"""
    Hack VM
    Read proc/PID/maps
    Read and write in proc/PID/mem
    Replace a word "A" to "B" allocate in the heap memory
"""
import sys


def print_info(f_pid, search_s, replace_s, start, end,
               index_search_s, s_line):
    """Print the process of read_write_heap module"""
    msg = "[*] maps: /proc/{}/maps\n".format(f_pid)
    msg += "[*] mem: /proc/{}/mem\n".format(f_pid)
    msg += "[*] Found [heap]:\n"
    msg += "\taddresses = {}\n".format(s_line[0])
    msg += "\tpermissions = {}\n".format(s_line[1])
    msg += "\toffset = {}\n".format(s_line[2])
    msg += "\tinode = {}\n".format(s_line[3])
    msg += "[*] Addr: "
    msg += "start [{}] | end [{}]\n".format(hex(start), hex(end))
    msg += "[*] Found: {} at {}\n".format(search_s, hex(index_search_s))
    msg += "[*] Writing: "
    msg += "{} at {}\n".format(replace_s, hex(start + index_search_s))

    print(msg, end="")


def main():
    """Replace a word "A" to "B" allocate in the heap memory"""
    if len(sys.argv) != 4:
        print("Usage: read_write_heap.py pid search_string replace_string")
        exit(1)
    f_pid = sys.argv[1]
    search_s = sys.argv[2]
    replace_s = sys.argv[3]

    try:
        maps_file = open("/proc/{}/maps".format(f_pid), 'r')
    except:
        print("{} no found active".format(f_pid))
        exit(1)

    try:
        mem_file = open("/proc/{}/mem".format(f_pid), 'r+b', 0)
    except:
        maps_file.close()
        print("{} no found active".format(f_pid))
        exit(1)

    heap_found = False
    for line in maps_file.readlines():
        s_line = line.split()
        if s_line[len(s_line) - 1] == "[heap]":
            heap_found = True
            range_mem = s_line[0].split('-')
            start = int(range_mem[0], 16)
            end = int(range_mem[1], 16)
            mem_file.seek(start)
            s = mem_file.read(end - start)
            index_search_s = s.find(bytes(search_s, 'utf-8'))

            if index_search_s == -1:
                break

            mem_file.seek(start + index_search_s)
            mem_file.write(bytes(replace_s, 'utf-8'))
            break

    maps_file.close()
    mem_file.close()

    if index_search_s == -1:
        print("\"{}\" no found in heap memory".format(search_s))
        exit(1)

    if not heap_found:
        print("No heap memory use in {} process".format(f_pid))
        exit(1)

    print_info(f_pid, search_s, replace_s, start, end,
               index_search_s, s_line)

if __name__ == "__main__":
    main()
