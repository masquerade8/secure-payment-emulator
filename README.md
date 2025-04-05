# secure-payment-emulator

# 🔐 Secure RFID Authentication System using Arduino Uno

This project demonstrates a **secure RFID-based access control system** using Arduino Uno and MFRC522. It implements a **challenge-response authentication** scheme based on XOR, combined with UID-based validation, to enhance the security of RFID transactions.

---

## 📽️ Demo Video

https://github.com/user-attachments/assets/5760d346-8486-4bad-a93b-b475db59af6c

---

## 📸 System in Action

### 🔄 Waiting for Card

![Scan Card](https://github.com/user-attachments/assets/f35d165c-a900-4dfe-9aa0-2b9f57238063)

> LCD prompts user to scan an RFID card.

---

### ❌ Invalid Card

![Invalid Card](https://github.com/user-attachments/assets/1ea44ed8-319c-462a-907f-814295813803)

> When an unauthorized card is scanned, LCD displays "Invalid Card".

---

### ✅ Access Granted

![Access Granted](https://github.com/user-attachments/assets/37f02a98-105e-4e06-bbb6-a051ccf12113)

> When an authorized card with correct challenge-response is scanned, LCD displays "Access Granted".

---

## ⚙️ How It Works

1. **Card UID Check**: Verifies if the scanned UID matches the authorized list.
2. **Read Key from Card**: Secret key is stored securely in sector 1, block 4 of the RFID tag.
3. **Challenge-Response**:
   - Arduino generates a 4-byte random challenge.
   - XORs the challenge with the card’s secret key to generate a response.
   - If the generated response matches the expected one, access is granted.
4. **Display Result**: LCD displays appropriate message based on verification.

---

## 🛠 Hardware Used

- Arduino Uno
- MFRC522 RFID Module
- RFID Tags or Cards
- I2C 16x2 LCD Display
- Breadboard & Jumper Wires
- Optional: LED for visual indication

---

## 🧪 Sample Output States

| LCD Display      | Meaning                          |
|------------------|----------------------------------|
| `Scan Card`      | Waiting for RFID tag             |
| `Invalid Card`   | Unauthorized or tampered card    |
| `Access Granted` | Valid card and correct response  |

---

## 🛠️ Setup Instructions

1. **Connect the Hardware**  
   - Arduino Uno  
   - MFRC522 RFID Reader  
   - I2C 16x2 LCD Display  
   - Breadboard, LEDs, Jumper Wires  
   - Power via USB

2. **Write Key to RFID Card**  
   Upload the `key_write.ino` sketch to the Arduino.  
   This will write a secure authentication key to your RFID card.  
   Place the card on the reader when prompted.

3. **Run the Emulator**  
   Upload the `emulator.ino` sketch to the Arduino.  
   This will start the sector-based challenge-response authentication system.  
   Scan the RFID card to see access granted or denied based on key match.

4. **Verify Output**  
   - LCD will display: `Scan Card`, `Access Granted`, or `Invalid Card` based on authentication.  
   - Use the attached images and video demo for visual reference.


---

