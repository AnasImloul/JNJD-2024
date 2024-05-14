xvariables = dict()


def to_str(s: memoryview):
    return s.tobytes().decode()


class Parser:
    @staticmethod
    def parse_parentheses(exp):
        depth = 1
        i = 1
        while i < len(exp) and depth > 0:
            if chr(exp[i]) == '(':
                depth += 1
            elif chr(exp[i]) == ')':
                depth -= 1
            i += 1
        return Parser.parse(exp[1:i - 1]), exp[i:]

    @staticmethod
    def parse_literal(exp):
        i = 1
        while i < len(exp) and chr(exp[i]) != '"':
            i += 1
        return to_str(exp[1: i]), exp[i + 1:]

    @staticmethod
    def parse_identifier(exp):
        i = 0
        while i < len(exp) and chr(exp[i]).isalpha():
            i += 1
        identifier = to_str(exp[:i])
        return variables.get(identifier, identifier), exp[i:]

    @staticmethod
    def parse_number(exp):
        n = exp[0] - ord('0')
        if chr(exp[2]) == '(':
            left, rest = Parser.parse_parentheses(exp[2:])
            return n * left, rest
        elif chr(exp[2]) == '"':
            left, rest = Parser.parse_literal(exp[2:])
            return n * left, rest
        elif chr(exp[2]).isalpha():
            left, rest = Parser.parse_identifier(exp[2:])
            return n * left, rest
        else:
            return n, exp[2:]

    @staticmethod
    def parse(exp):
        if not exp:
            return ""
        if chr(exp[0]) == '(':
            left, rest = Parser.parse_parentheses(exp)
            return left + Parser.parse(rest)
        elif chr(exp[0]) == '"':
            left, rest = Parser.parse_literal(exp)
            return left + Parser.parse(rest)
        elif chr(exp[0]).isalpha():
            left, rest = Parser.parse_identifier(exp)
            return left + Parser.parse(rest)
        elif chr(exp[0]).isdigit():
            left, rest = Parser.parse_number(exp)
            return left + Parser.parse(rest)
        elif chr(exp[0]) == '+':
            return Parser.parse(exp[1:])


def main():
    for _ in range(int(input())):
        command, rest = input().split(' ', 1)
        if command == 'set':
            key, value = rest.split(' = ', 1)
            value = memoryview("".join(value.split()).encode())
            variables[key] = Parser.parse(value)
        elif command == 'get':
            print(variables.get(rest, rest))


if __name__ == '__main__':
    main()
