import os
from dotenv import load_dotenv

# Load .env from parent directory
load_dotenv()

API_TOKEN = os.getenv("API_TOKEN")