variables = dict()


class Parser:
    def __init__(self, exp):
        self.exp = exp
        self.match = [-1 for _ in range(len(exp))]
        s = []
        for i, c in enumerate(exp):
            if c == '(':
                s.append(i)
            elif c == ')':
                self.match[s.pop()] = i

    def parse_parentheses(self, i, j):
        k = self.match[i]
        return self.parse(i + 1, k), k + 1

    def parse_literal(self, i, j):
        k = i + 1
        while k < j and self.exp[k] != '"':
            k += 1
        return self.exp[i + 1: k], k + 1

    def parse_identifier(self, i, j):
        k = i
        while k < j and self.exp[k].isalpha():
            k += 1
        identifier = self.exp[i:k]
        return variables.get(identifier, identifier), k

    def parse_number(self, i, j):
        n = int(self.exp[i])
        if self.exp[i + 2] == '(':
            left, k = self.parse_parentheses(i + 2, j)
            return n * left, k
        elif self.exp[i + 2] == '"':
            left, k = self.parse_literal(i + 2, j)
            return n * left, k
        elif self.exp[i + 2].isalpha():
            left, k = self.parse_identifier(i + 2, j)
            return n * left, k
        else:
            return n, i + 2

    def parse(self, i, j):
        if i == j:
            return ""
        if self.exp[i] == '(':
            left, k = self.parse_parentheses(i, j)
            return left + self.parse(k, j)
        elif self.exp[i] == '"':
            left, k = self.parse_literal(i, j)
            return left + self.parse(k, j)
        elif self.exp[i].isalpha():
            left, k = self.parse_identifier(i, j)
            return left + self.parse(k, j)
        elif self.exp[i].isdigit():
            left, k = self.parse_number(i, j)
            return left + self.parse(k, j)
        elif self.exp[i] == '+':
            return self.parse(i + 1, j)


def main():
    for _ in range(int(input())):
        command, rest = input().split(' ', 1)
        if command == 'set':
            key, value = rest.split(' = ', 1)
            exp = "".join(value.split())
            parser = Parser("".join(value.split()))
            variables[key] = parser.parse(0, len(exp))
        elif command == 'get':
            print(variables.get(rest, rest))


if __name__ == '__main__':
    main()
