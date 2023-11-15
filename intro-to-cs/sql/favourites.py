from cs50 import SQL

db = SQL("sqlite:///favourites.db")

favourite = input("Favourite: ")

rows = db.execute("SELECT COUNT(*) AS n FROM favourites WHERE problem = ?", favourite)

print(rows[0]["n"])
