class Jar:
    def __init__(self, capacity=12):
        if isinstance(capacity, int) and capacity >= 0:
            self._capacity = capacity
            self._size = 0
        elif not isinstance(capacity, int):
            raise ValueError("Input capacity is not of integer type")
        else:
            raise ValueError("Input capacity should be non-negative")

    def __str__(self):
        return "🍪" * self.size

    def deposit(self, n):
        if self.size + n > self.capacity:
            raise ValueError(
                f"Cannot deposit n={n} cookies 🍪 in a Jar with size {self.size} and maximum capacity {self.capacity}"
            )
        else:
            self._size += n

    def withdraw(self, n):
        if self.size - n < 0:
            raise ValueError(
                f"Cannot withdraw n={n} cookies 🍪 from a Jar with size {self.size}"
            )
        else:
            self._size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size


def main():
    jar = Jar()
    print(str(jar.capacity))
    print(jar)
    jar.deposit(2)
    print(str(jar))
    jar.withdraw(1)
    print(str(jar))
    jar.deposit(6)
    print(str(jar))


if __name__ == "__main__":
    main()
