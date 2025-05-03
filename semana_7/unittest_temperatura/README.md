# 🧪 Prática - Testes Unitários com Unity no Raspberry Pi Pico  

*Um projeto demonstrativo de implementação de testes unitários em sistemas embarcados usando a biblioteca Unity.  
Focado na validação de leituras do sensor de temperatura interno do RP2040.*  

---

## 📋 Visão Geral  
Este projeto exemplifica como estruturar testes unitários para firmware embarcado, garantindo precisão e robustez em:  
1. **Conversão de valores ADC para Celsius**  
2. **Leitura direta do sensor de temperatura do RP2040**  

Ideal para desenvolvedores que buscam integrar testes automatizados em projetos com Raspberry Pi Pico/Pico W.  

---

## 🛠️ Funcionalidades Principais  

### ✅ Teste 1: Validação da Função `adc_to_celsius`  
- **Objetivo**: Garantir que a conversão de valores ADC (12 bits) para Celsius segue a fórmula esperada.  
- **Entrada**: Valor ADC simulado `866`.  
- **Saída Esperada**: `27.0°C` com margem de erro de `±0.1°C`.  
- **Relevância**: Assegura que cálculos matemáticos estão corretos, mesmo sem acesso ao hardware.  

### ✅ Teste 2: Validação da Função `hal_temperature_read_rp2040`  
- **Objetivo**: Verificar a leitura real do sensor de temperatura interno.  
- **Entrada**: Leitura direta do ADC do sensor.  
- **Saída Esperada**: `27.0°C` com margem de erro de `±5.0°C` (considerando variações ambientais).  
- **Relevância**: Confirma que o sensor opera dentro de parâmetros realistas.  

---

## 📂 Estrutura do Projeto  
```plaintext
📁 /  
├── 📁 app/ → Lógica principal da aplicação 🧠
│ └── main.c → Implementação do loop principal
├── 📁 drivers/ → Controle direto de hardware 🔌
│ └── led_dentro.c → Driver específico do LED embutido
├── 📁 hal/ → Camada de abstração de hardware ⚙️
├── 📁 include/ → Headers (Unity, definições de hardware)
├── 📁 test/ → Casos de teste unitários 
└── CMakeLists.txt → Configuração de build  