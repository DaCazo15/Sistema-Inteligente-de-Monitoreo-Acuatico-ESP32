# Configuracion de la aplicacion
# ==================================================================

from src.serial_ESP32.serialCom import puerto

# URL de Key de Supabase
SUPABASE_URL = "https://obdbtsmggdoedscydrob.supabase.co"
SUPABASE_KEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im9iZGJ0c21nZ2RvZWRzY3lkcm9iIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDg5OTE5NTMsImV4cCI6MjA2NDU2Nzk1M30.fUp5k5ECXePpMG1l8e_GZFOQKE_IArLvxg9gzfPm7hQ"

# Puerto serie y velocidad de baudios
PUERTO_SERIAL = puerto()  
BAUDRATE = 115200

# Llaves de la API de OpenAI
OPENAI_API_KEY = "AIzaSyDrtAItKcwciddWR99m44uNqfM7OJafroY"
MODEOL_ID = "gemini-2.0-flash"