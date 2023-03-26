import csv
from cs50 import SQL


def insert_student(name: str, db: SQL) -> int:
    query = """
        SELECT
            *
        FROM
            students
        WHERE
            name = ?
    """
    rows = db.execute(query, name)
    if rows:
        return rows[0]["id"]
    else:
        db.execute(
            """
            INSERT INTO
                students (name)
            VALUES
                (?)""",
            name,
        )
        rows = db.execute(query, name)
        return rows[0]["id"]


def insert_house(name: str, head: str, db: SQL) -> int:
    query = """
        SELECT
            *
        FROM
            houses
        WHERE
            name = ?
        AND
            head = ?
    """
    rows = db.execute(query, name, head)
    if rows:
        return rows[0]["id"]
    else:
        db.execute(
            """
            INSERT INTO
                houses (name, head)
            VALUES
                (?, ?)""",
            name,
            head,
        )
        rows = db.execute(query, name, head)
        return rows[0]["id"]


def insert_assignment(student_id: int, house_id: int, db: SQL) -> None:
    query = """
        SELECT
            *
        FROM
            assignments
        WHERE
            student_id = ?
        AND
            house_id = ?
    """
    rows = db.execute(query, student_id, house_id)
    if not rows:
        db.execute(
            """
            INSERT INTO
                assignments (student_id, house_id)
            VALUES
                (?, ?)""",
            student_id,
            house_id,
        )


if __name__ == "__main__":
    db = SQL(url="sqlite:///new_roster.db")

    with open(file="students.csv", mode="r") as file:
        reader = csv.DictReader(file)
        for row in reader:
            student_id = insert_student(name=row["student_name"], db=db)
            house_id = insert_house(name=row["house"], head=row["head"], db=db)
            insert_assignment(student_id=student_id, house_id=house_id, db=db)
