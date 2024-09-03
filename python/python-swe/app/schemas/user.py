from pydantic import BaseModel
from typing import Optional


class User(BaseModel):
    username: str
    short_description: str
    liked_posts: Optional[list[int]]
