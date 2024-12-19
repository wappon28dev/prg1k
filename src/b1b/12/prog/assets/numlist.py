import random


def main() -> None:
    with open("numlist.txt", "w") as f:
        for _ in range(256):
            f.write(f"{random.randint(0, 100)}\n")


if __name__ == "__main__":
    main()
