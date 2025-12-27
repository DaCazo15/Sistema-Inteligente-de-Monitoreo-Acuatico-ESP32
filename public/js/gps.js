// Este script obtiene los últimos datos de un dispositivo IoT desde Supabase
// Actualiza la UI en tiempo real.
// ========================================================================================
const SUPABASE_URL = "https://obdbtsmggdoedscydrob.supabase.co";
const SUPABASE_KEY = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6Im9iZGJ0c21nZ2RvZWRzY3lkcm9iIiwicm9sZSI6ImFub24iLCJpYXQiOjE3NDg5OTE5NTMsImV4cCI6MjA2NDU2Nzk1M30.fUp5k5ECXePpMG1l8e_GZFOQKE_IArLvxg9gzfPm7hQ"

const TABLE = "gps";

// Obtiene el último registro y actualiza la UI
async function getLastData() {
    const endpoint = `${SUPABASE_URL}/rest/v1/${TABLE}?select=latitud,longitud,altitud,updated_at&order=updated_at.desc&limit=1`;
    const res = await fetch(endpoint, {
        headers: {
            apikey: SUPABASE_KEY,
            Authorization: `Bearer ${SUPABASE_KEY}`
        }
    });
    const data = await res.json();
    if (data.length > 0) {
        const lat = Number(data[0].latitud);
        const lng = Number(data[0].longitud);
        document.getElementById('latitude').textContent = lat.toFixed(6);
        document.getElementById('longitude').textContent = lng.toFixed(6);
        document.getElementById('altitude').textContent = Number(data[0].altitud).toFixed(2);

        // Actualiza el marcador en el mapa
        if (typeof actualizarMarcador === "function") {
            actualizarMarcador(lat, lng);
        }
    } else {
        document.getElementById('latitude').textContent = "Sin datos";
        document.getElementById('longitude').textContent = "Sin datos";
        document.getElementById('altitude').textContent = "Sin datos";
    }
}

getLastData();
setInterval(getLastData, 250); // Actualiza cada 250 ms