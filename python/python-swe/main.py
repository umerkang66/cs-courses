# pip freeze > requirements.txt
# python.exe -m pip install --upgrade pip
# export PIPENV_VENV_IN_PROJECT=1
# uvicorn main:app --reload

from typing import Optional
from fastapi import FastAPI
from pydantic import BaseModel


app = FastAPI()


class User(BaseModel):
    username: str
    short_description: str
    liked_posts: Optional[list[int]]


def get_user_info() -> tuple[str, str]:
    username = "test_user"
    short_description = "my bio description"
    return username, short_description


@app.get("/user/me", response_model=User)
def me():
    username, short_description = get_user_info()
    user = User(
        username=username, short_description=short_description, liked_posts=[1, 2, 3]
    )
    return user
