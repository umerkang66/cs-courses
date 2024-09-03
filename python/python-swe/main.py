# pip freeze > requirements.txt
# python.exe -m pip install --upgrade pip
# export PIPENV_VENV_IN_PROJECT=1
# uvicorn main:app --reload

from fastapi import FastAPI
from app import create_user_router


def create_application() -> FastAPI:
    user_router = create_user_router()

    app = FastAPI()
    app.include_router(user_router)

    return app


app = create_application()
