import codecs, sys
from collections import defaultdict

def form_dict_from_file(file_name):

    id_phone = defaultdict(lambda: [])

    with codecs.open(file_name, 'r', 'utf-8') as f:
        for line in f:
            line = line.strip()
            if len(line):
                phones_id = line.split('=')[1].split('#')
                phone = phones_id[0]
                id = phones_id[1]
                id_phone[id].append(phone)

    return id_phone

def compare_dicts(d1, d2):
    for id in d1.keys():
        assert sorted(d1[id]) == sorted(d2[id])


if __name__ == "__main__":
    file_1 = sys.argv[1]
    file_2 = sys.argv[2]

    compare_dicts( form_dict_from_file(file_1), form_dict_from_file(file_1) )