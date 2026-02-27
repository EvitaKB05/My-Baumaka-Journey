from reportlab.lib.pagesizes import A4
from reportlab.lib.units import cm
from reportlab.pdfgen import canvas
from reportlab.lib.colors import Color, black, blue, red, green

def create_structural_diagram(filename="structural_diagram_v43.pdf"):
    c = canvas.Canvas(filename, pagesize=A4)
    width, height = A4
    
    # Заголовок
    c.setFont("Helvetica-Bold", 14)
    c.drawString(5*cm, height-2*cm, "СТРУКТУРНАЯ СХЕМА ОПЕРАЦИОННОГО АВТОМАТА")
    c.setFont("Helvetica", 10)
    c.drawString(5*cm, height-2.5*cm, "Вариант 43. Разрядность: 10 бит. Серия К500")
    
    # Основные блоки (координаты)
    blocks = {
        "ШВХ": (1*cm, height-4*cm),
        "ША": (3*cm, height-4*cm),
        "MS_A": (1*cm, height-6*cm),
        "MS_B": (3*cm, height-6*cm),
        "MS_C": (5*cm, height-6*cm),
        "РгА": (1*cm, height-8*cm),
        "РгB": (3*cm, height-8*cm),
        "РгC": (5*cm, height-8*cm),
        "АЛУ1": (2*cm, height-12*cm),
        "АЛУ2": (4*cm, height-12*cm),
        "АЛУ3": (6*cm, height-12*cm),
        "SIGN_A": (1*cm, height-14*cm),
        "SIGN_B": (3*cm, height-14*cm),
        "SIGN_D": (5*cm, height-14*cm),
        "MS_OUTPUT": (3*cm, height-16*cm),
        "ШВЫХ": (3*cm, height-18*cm),
        "ЗАН": (1*cm, height-20*cm),
        "ГОТ": (3*cm, height-20*cm),
        "ПР": (5*cm, height-20*cm),
    }
    
    # Рисуем блоки
    for name, (x, y) in blocks.items():
        c.rect(x, y, 2*cm, 0.8*cm)
        c.setFont("Helvetica", 8)
        c.drawString(x+0.1*cm, y+0.5*cm, name)
    
    # Подписи управляющих сигналов
    c.setFont("Helvetica", 7)
    y_signals = height-22*cm
    c.drawString(10*cm, y_signals, "Управляющие сигналы:")
    signals = [
        "Y0,Y1 - Регистр A",
        "Y2,Y3 - Регистр B",
        "Y4,Y5 - Регистр C",
        "Y6,Y7 - Рг D0",
        "Y8,Y9 - Рг D1",
        "Y10-Y16 - АЛУ",
        "Y17-Y19 - MS OP A",
        "Y20-Y22 - MS OP B",
        "Y23-Y32 - Знаки",
        "Y33-Y46 - Вывод/упр.",
        "Y45 - Разр. знака",
        "Y46 - Сброс D"
    ]
    
    for i, signal in enumerate(signals):
        c.drawString(10*cm, y_signals - (i+1)*0.4*cm, signal)
    
    # Штамп
    c.setFont("Helvetica", 8)
    c.drawString(14*cm, 2*cm, "Лист 4")
    c.drawString(14*cm, 1.7*cm, "Операционный автомат.")
    c.drawString(14*cm, 1.4*cm, "Схема структурная электрическая.")
    c.drawString(14*cm, 1.1*cm, "Вариант 43")
    c.drawString(14*cm, 0.8*cm, "МГТУ им. Н.Э. Баумана")
    c.drawString(14*cm, 0.5*cm, "Группа ИУ5-52")
    
    c.save()
    print(f"PDF создан: {filename}")

# Создаём PDF
create_structural_diagram()