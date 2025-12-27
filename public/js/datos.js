// Este script obtiene los últimos datos de un dispositivo IoT desde Supabase
// Actualiza la UI en tiempo real.
// ========================================================================================
const SUPABASE_URL = "https://obdbtsmggdoedscydrob.supabase.co";
const SUPABASE_KEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im9iZGJ0c21nZ2RvZWRzY3lkcm9iIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDg5OTE5NTMsImV4cCI6MjA2NDU2Nzk1M30.fUp5k5ECXePpMG1l8e_GZFOQKE_IArLvxg9gzfPm7hQ"

const TABLE = "datos";

// Obtiene el último registro y actualiza la UI
async function getLastData() {
    const endpoint = `${SUPABASE_URL}/rest/v1/${TABLE}?select=v1,v2,v3,updated_at&order=updated_at.desc&limit=1`;
    const res = await fetch(endpoint, {
        headers: {
            apikey: SUPABASE_KEY,
            Authorization: `Bearer ${SUPABASE_KEY}`
        }
    });
    const data = await res.json();
    if (data.length > 0) {
        // v1 = temperatura, v2 = humedad, v3 = presión (bool)
        document.getElementById('temperature').textContent = Number(data[0].v1).toFixed(2);
        document.getElementById('humidity').textContent = Number(data[0].v2).toFixed(2);
        document.getElementById('pressure').textContent = data[0].v3 + "º";
    } else {
        document.getElementById('temperature').textContent = "Sin datos";
        document.getElementById('humidity').textContent = "Sin datos";
        document.getElementById('pressure').textContent = "Sin datos";
    }
}
getLastData();
setInterval(getLastData, 250); // Actualiza cada 250 ms