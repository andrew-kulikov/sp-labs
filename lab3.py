class List:
    def __init__(self):
        self.begin = None
        self.end = None

    class __Node:
        def __init__(self):
            self.next = None
            self.prev = None
            self.data = None

    def push_front(self, data):
        node = self.__Node()
        node.data = data

        if self.begin:
            node.prev = self.begin
            self.begin.next = node
            self.begin = node
        else:
            self.begin = node
            self.end = node

    def push_back(self, data):
        node = self.__Node()
        node.data = data

        if self.begin:
            node.next = self.end
            self.end.prev = node
            self.end = node
        else:
            self.begin = node
            self.end = node

    def remove(self, n):
        tmp = self.end
        i = 0
        while tmp:
            if i == n:
                if self.end == self.begin:
                    self.end = None
                    self.begin = None
                    return
                if tmp == self.end:
                    self.end = self.end.next
                    self.end.prev = None
                elif tmp == self.begin:
                    self.begin = self.begin.prev
                    self.begin.next = None
                else:
                    tmp.prev.next = tmp.next
                    tmp.next.prev = tmp.prev
                    tmp = None
                break
            i += 1
            tmp = tmp.next

    def clear(self):
        tmp = self.end
        while tmp:
            tmp = tmp.next
            self.remove(0)

    def print(self):
        tmp = self.end
        while tmp:
            print(tmp.data)
            tmp = tmp.next


def main():
    lst = List()
    lst.push_front('5')
    lst.push_front('10')
    lst.push_front('15')
    lst.push_back('21')
    lst.remove(0)
    lst.push_back('22')
    lst.remove(4)
    lst.clear()
    lst.print()


if __name__ == '__main__':
    main()
