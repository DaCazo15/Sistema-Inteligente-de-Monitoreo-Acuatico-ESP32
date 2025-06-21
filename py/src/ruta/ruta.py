import google.generativeai as genai
from config.config import *

def localizacion(locationA, locationB):
    genai.configure(api_key=OPENAI_API_KEY)
    model = genai.GenerativeModel(MODEOL_ID)

    user_message = f"Quiero llegar mas rapido del punto {locationA} al punto {locationB}."

    try:
        response = model.generate_content(user_message)
        return response.text
    except Exception as e:
        return f"Error: {e}"
