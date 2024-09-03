from fastapi import APIRouter
from app.schemas import User
from app.services import UserService


def create_user_router() -> APIRouter:
    user_router = APIRouter(prefix="/user", tags=["user"])

    @user_router.get("/me", response_model=User)
    def me():
        username, short_description = UserService.get_user_info()
        user = User(
            username=username,
            short_description=short_description,
            liked_posts=[1, 2, 3],
        )
        return user

    return user_router
