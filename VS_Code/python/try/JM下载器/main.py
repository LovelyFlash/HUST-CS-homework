import os
import re
from PIL import Image
from fpdf import FPDF
import glob

def is_valid_number_folder(folder_name):
    """检查文件夹名是否只包含数字"""
    return re.fullmatch(r'\d+', folder_name) is not None

def is_valid_number_file(file_name):
    """检查文件名是否只包含数字和图片扩展名"""
    return re.fullmatch(r'\d+\.(jpg|jpeg|png|bmp|gif)', file_name, re.IGNORECASE) is not None

def images_to_pdf(image_paths, output_path):
    """将多张图片合并为一个PDF文件"""
    if not image_paths:
        return False
    
    # 使用Pillow打开所有图片并转换为PDF
    try:
        images = [Image.open(img) for img in image_paths]
        # 保存为PDF（Pillow方式）
        images[0].save(
            output_path, "PDF", 
            resolution=100.0, 
            save_all=True, 
            append_images=images[1:]
        )
        return True
    except Exception as e:
        print(f"转换PDF失败: {e}")
        return False

def process_folder(root_folder):
    """处理主文件夹"""
    if not os.path.isdir(root_folder):
        print(f"错误: 路径 {root_folder} 不是一个有效的文件夹")
        return
    
    for folder_name in os.listdir(root_folder):
        folder_path = os.path.join(root_folder, folder_name)
        
        # 只处理数字命名的子文件夹
        if os.path.isdir(folder_path) and is_valid_number_folder(folder_name):
            print(f"\n处理文件夹: {folder_name}")
            
            # 检查是否已存在PDF文件
            pdf_files = glob.glob(os.path.join(folder_path, '*.pdf'))
            if pdf_files:
                print(f"已存在PDF文件，跳过: {pdf_files[0]}")
                continue
            
            # 获取所有数字命名的图片文件
            image_files = []
            for file_name in os.listdir(folder_path):
                if is_valid_number_file(file_name):
                    image_files.append(os.path.join(folder_path, file_name))
            
            if not image_files:
                print("没有找到有效的图片文件")
                continue
            
            # 按数字顺序排序图片
            image_files.sort(key=lambda x: int(re.search(r'\d+', os.path.basename(x)).group()))
            
            # 生成PDF文件名
            pdf_path = os.path.join(folder_path, f"{folder_name}.pdf")
            
            print(f"找到 {len(image_files)} 张图片，正在转换为PDF...")
            if images_to_pdf(image_files, pdf_path):
                print(f"成功生成PDF: {pdf_path}")
            else:
                print("生成PDF失败")

if __name__ == "__main__":
    print("图片转PDF工具")
    folder_path = input("请输入文件夹路径: ").strip()
    process_folder(folder_path)
    print("\n处理完成!")
