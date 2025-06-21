var lat_esp32 = 11.030510;
var lng_esp32 = -63.843452;
var marker, map;

function iniciarMap() {
    var coord = { lat: lat_esp32, lng: lng_esp32 };	
    map = new google.maps.Map(document.getElementById('map'), {
        center: coord,
        zoom: 10
    });
    marker = new google.maps.Marker({
        position: coord,
        map: map
    });
}

// Llama a esta función cada vez que cambien lat_esp32 y lng_esp32
function actualizarMarcador(lat, lng) {
    lat_esp32 = lat;
    lng_esp32 = lng;
    var nuevaPos = { lat: lat_esp32, lng: lng_esp32 };
    marker.setPosition(nuevaPos);
    map.setCenter(nuevaPos);
}