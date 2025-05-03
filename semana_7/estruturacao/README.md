# 🚀 Projeto LED Modularizado - Pico W 

**✨ Uma estrutura moderna para controle de LEDs no Raspberry Pi Pico W, com organização modular e boas práticas de desenvolvimento embarcado!**

---

## 📋 Descrição

Este projeto é uma evolução do exemplo padrão `blink_w`, reorganizado em uma arquitetura modular e escalável 🧱. O objetivo é facilitar a manutenção, reutilização de código e implementação de novas funcionalidades, seguindo princípios de **Hardware Abstraction Layer (HAL)** e separação de responsabilidades.

**Destaques:**  
✅ 100% compatível com Raspberry Pi Pico W  
✅ Código documentado e intuitivo  
✅ Interface simples para controle de LEDs  
✅ Estrutura pronta para expansões futuras  

---

## 🗂️ Estrutura do Projeto
```plaintext
📁 /
├── 📁 app/ → Lógica principal da aplicação 🧠
│ └── main.c → Implementação do loop principal
├── 📁 drivers/ → Controle direto de hardware 🔌
│ └── led_dentro.c → Driver específico do LED embutido
├── 📁 hal/ → Camada de abstração de hardware ⚙️
│ └── hal_led.c → API simplificada para controle de LEDs
└── 📁 include/ → Cabeçalhos e interfaces 📄
  ├── hal_led.h
  └── led_dentro.h
