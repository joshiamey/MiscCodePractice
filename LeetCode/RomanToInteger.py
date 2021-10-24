def romanToInt(s):
    """Function to convert a roman string to integer"""

    roman_to_int_dict = {
        "I": 1,
        "V": 5,
        "X": 10,
        "L": 50,
        "C": 100,
        "D": 500,
        "M": 1000,
    }
    
    result = 0
    prev_char = ""
    for char in s:
        result += roman_to_int_dict[char]

        # its Either IX or IV , we have added +1 from I and +1 from (X or V)
        # hence substract 1 from the previous I and 1 for (X or V)
        if prev_char == "I" and char in ["X", "V"]:
            result -= 2

        # its Either XL or XV , we have added +10 from X and +10 from (L or C)
        # hence substract 10 from the previous X and 10 for (L or C)

        if prev_char == "X" and char in ["L", "C"]:
            result -= 20

        # its Either CD or CM , we have added +100 from C and +100 from (D or M)
        # hence substract 100 from the previous C and 100 for (D or M)
        if prev_char == "C" and char in ["D", "M"]:
            result -= 200

        prev_char = char

    return result


if __name__ == "__main__":
    print(romanToInt("IX"))
