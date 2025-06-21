from supabase import create_client, Client
from config.config import *
cont = 0
def get_last_location():
    supabase: Client = create_client(SUPABASE_URL, SUPABASE_KEY)
    response = supabase.table("gps").select("longitud").order("updated_at", desc=True).limit(1).execute() 
    if response.data and len(response.data) > 0:
        return response.data[0]["longitud"]
    else:
        return None

def insert_new_gps(longitud_A, longitud_B):
    global cont
    supabase: Client = create_client(SUPABASE_URL, SUPABASE_KEY)
    direccion = 1 if longitud_B > longitud_A else 0

    if longitud_B > longitud_A:
        cont += 1
    if cont > 2:
        direccion = 0
        cont = 0
        
    # Insert the new GPS data with the direction
    data = {
        "direccion": direccion,
    }
    response = supabase.table("nuevo_gps").insert(data).execute()
    return response
