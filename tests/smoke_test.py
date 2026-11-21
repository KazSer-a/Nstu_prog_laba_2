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
        if hash_result.count("вставлено 5/5") != 2:
            raise AssertionError(f"{language}: отрицательные ключи не обработаны: {hash_result}")
        for source, expected in [("2 2 1", "2 1 2"), ("2 # 1 # 1", "1 # 1 # 2")]:
            assert run(binary + ["5"], source + "\n") == expected, (language, source)
        duplicate_hash = run(binary + ["6"], "4 5\n1 1 6 11\n").splitlines()
        assert len(duplicate_hash) == 2, language
        assert "вставлено 3/4, проверено ячеек 7" in duplicate_hash[0], (language, duplicate_hash)
        assert "вставлено 3/4, проверено ячеек 6" in duplicate_hash[1], (language, duplicate_hash)
        assert run(binary + ["7"], "3\nA B\nA B\nB B\n") == "A 0\nB 1", language
        assert "несколько менеджеров" in run(binary + ["7"], "2\nA B\nA C\n"), language

        commands = [f"SETADD k{i}" for i in range(80)]
        commands += [f"SETDEL k{i}" for i in range(0, 80, 2)]
        commands += [f"SETADD k{i}" for i in range(80, 160)]
        commands += [f"SET_AT k{i}" for i in range(160)]
        expected = ["FALSE" if i < 80 and i % 2 == 0 else "TRUE" for i in range(160)]
        batch = str(len(commands)) + "\n" + "\n".join(commands) + "\n"
        assert run(binary + ["2"], batch).splitlines() == expected, language
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
