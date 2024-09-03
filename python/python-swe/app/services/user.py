class UserService:
    @staticmethod
    def get_user_info() -> tuple[str, str]:
        username = "test_user"
        short_description = "my bio description"
        return username, short_description
