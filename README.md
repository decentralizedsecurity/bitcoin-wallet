# bitcoin-wallet

## Descripción

`bitcoin-wallet` es una billetera de hardware para Bitcoin que permite a los usuarios generar claves ECDSA, firmar mensajes y realizar otras operaciones criptográficas de manera segura. Esta billetera está diseñada para funcionar en dispositivos basados en la plataforma nRF, aprovechando las capacidades de seguridad y conectividad del hardware de Nordic Semiconductor, específicamente en las placas nRF9160 y nRF5340.

## Requisitos Previos

Antes de comenzar a trabajar con el proyecto, asegúrate de tener lo siguiente instalado y configurado en tu entorno de desarrollo:

1. **nRF Connect SDK v2.6.0**: Utilizado para el desarrollo de aplicaciones basadas en los SoCs de Nordic Semiconductor. Instrucciones de instalación en el [sitio oficial de Nordic Semiconductor](https://www.nordicsemi.com/Software-and-tools/Development-Tools/nRF-Connect-SDK).

2. **Placas de desarrollo soportadas**:
   - **nRF9160 DK**: Utilizada para el firmware de la carpeta `build`.
   - **nRF5340 DK**: Utilizada para el firmware de la carpeta `build_1`.

3. **Herramientas de desarrollo**:
   - **Visual Studio Code**: Recomendado con las extensiones de Nordic Semiconductor instaladas, como `nRF Connect`, `nRF DeviceTree`, `nRF Kconfig`, y `nRF Terminal`.
   - **CMake**: Para gestionar la configuración y construcción del proyecto.
   - **GNU ARM Toolchain**: Para compilar el firmware para las placas nRF.

4. **Configuración del entorno**:
   - Clona el repositorio del proyecto e instala los requisitos previos mencionados.
   - Configura el entorno siguiendo las instrucciones de Nordic para utilizar nRF Connect SDK.

## Directorios de Builds

- build/: Este directorio contiene la configuración y compilación para la nRF9160 DK.

- build_1/: Contiene la configuración y compilación para la nRF5340 DK.