# src/auth.py
from fastapi import Header, HTTPException, Depends
from src.config import API_TOKEN

def verify_token(authorization: str = Header(...)):
    if not authorization.startswith("Bearer "):
        raise HTTPException(status_code=401, detail="Missing or invalid Authorization header")
    
    token = authorization.split("Bearer ")[-1]
    if token != API_TOKEN:
        raise HTTPException(status_code=403, detail="Invalid token")
