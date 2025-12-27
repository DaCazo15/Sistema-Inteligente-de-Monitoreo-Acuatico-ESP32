import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";

console.log("script.js cargado correctamente");

const firebaseConfig = {
  apiKey: "AIzaSyB8rMCREuzjsK8ly1H7fZRxoGeeo1JZ_vg",
  authDomain: "limpiador-3cca3.firebaseapp.com",
  projectId: "limpiador-3cca3",
  storageBucket: "limpiador-3cca3.firebasestorage.app",
  messagingSenderId: "904476949531",
  appId: "1:904476949531:web:c3e0f679d2bf9517898cbe",
  measurementId: "G-7NJ1SL6QJE"
};

const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);