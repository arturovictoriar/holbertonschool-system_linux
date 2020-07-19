#!/usr/bin/python3


def canUnlockAll(boxes):
    """open all boxes"""
    lenght_boxes = len(boxes)

    def hola(j, keys, lenght_boxes):
        keys[j] = 1
        if len(keys) == lenght_boxes:
            return keys
        all_keys = keys
        for i in boxes[j]:
            if i not in keys or keys[i] == 0:
                j = i
                all_keys = hola(j, keys, lenght_boxes)
        return all_keys

    if len(hola(0, {}, lenght_boxes)) == lenght_boxes:
        return True
    return False
