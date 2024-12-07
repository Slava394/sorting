import random as rd
import string as st


with open("./test/test_data/int_data.txt", "w") as f:
    for i in range(1000):
        f.write(str(rd.randint(-5000000, 5000000)) + "\n")

with open("./test/test_data/double_data.txt", "w") as f:
    for i in range(1000):
        offset = rd.randint(-5000000, 5000000)
        f.write(str((offset + 1.0) / 1000000.0) + "\n")

with open("./test/test_data/string_data.txt", "w") as f:
    letters = st.ascii_letters
    for i in range(1000):
        length = rd.randint(1, 56)
        f.write("".join(rd.choice(letters) for i in range(length)) + "\n")