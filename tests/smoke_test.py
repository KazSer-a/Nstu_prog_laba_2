#!/usr/bin/env python3
"""Сборка и проверка основных сценариев C++ и Go."""
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
GO_DIR = ROOT / "go"
CASES = {
    "1": ("3 2\nA B C\nA B\nB C\n", "Возможно"),
    "2": ("5\nSETADD cat\nSET_AT cat\nSETDEL cat\nSET_AT cat\nSET_AT dog\n", "TRUE\nFALSE\nFALSE"),
    "3": ("ABBACAB BCABB\n", "4"),
    "4": ("4\ncAnnot\ncannOt\nfOund\npAge\nthE pAge cAnnot be fouNd\n", "2"),
    "5": ("6 2 8 # 4 5 #\n", "5 2 8 # 4 6"),
    "7": ("5\nA B\nC B\nD E\nB E\nE E\n", "A 0\nB 2\nC 0\nD 0\nE 4"),
    "8": ("2 8\nSET 1 2\nSET 2 3\nSET 1 5\nSET 4 5\nSET 6 7\nGET 4\nSET 1 2\nGET 3\n", "5 -1"),
}


def run(command, data="", cwd=ROOT):
    result = subprocess.run(command, input=data, text=True, capture_output=True, cwd=cwd)
    if result.returncode != 0:
        raise AssertionError(f"Команда {command} завершилась с ошибкой:\n{result.stderr}\n{result.stdout}")
    return result.stdout.strip()


def main():
    run(["make", "-C", str(ROOT / "cpp"), "clean"])
    run(["make", "-C", str(ROOT / "cpp")])
    run(["go", "test", "./..."], cwd=GO_DIR)
    run(["go", "build", "-o", "laba2", "."], cwd=GO_DIR)
    programs = {"C++": [str(ROOT / "cpp" / "laba2")], "Go": [str(GO_DIR / "laba2")]}
    for language, binary in programs.items():
        for task, (source, expected) in CASES.items():
            actual = run(binary + [task], source)
            if actual != expected:
                raise AssertionError(f"{language}, задание {task}: ожидалось {expected!r}, получено {actual!r}")
        cycle = "4 4\nA B C D\nA B\nA D\nB C\nC A\n"
        if run(binary + ["1"], cycle) != "Невозможно":
            raise AssertionError(f"{language}: цикл зависимостей не обнаружен")
        hash_result = run(binary + ["6"], "5 11\n-11 -22 -33 -44 -55\n")
        if "вставлено 5/5" not in hash_result:
            raise AssertionError(f"{language}: отрицательные ключи не обработаны: {hash_result}")
        with tempfile.TemporaryDirectory() as directory:
            data_file = Path(directory) / "set.txt"
            data_file.write_text("cat\ndog\n", encoding="utf-8")
            checks = [("SET_AT cat", "TRUE"), ("SETADD fox", "OK"), ("SET_AT fox", "TRUE"),
                      ("SETDEL cat", "OK"), ("SET_AT cat", "FALSE")]
            for query, expected in checks:
                actual = run(binary + ["--file", str(data_file), "--query", query])
                if actual != expected:
                    raise AssertionError(f"{language}, запрос {query}: ожидалось {expected!r}, получено {actual!r}")
        print(f"{language}: сборка и проверки пройдены")
    print("Все проверки успешно завершены.")


if __name__ == "__main__":
    main()
