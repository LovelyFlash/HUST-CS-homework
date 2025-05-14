import jmcomic

def main():
    # Initialize the downloader
    downloader = jmcomic.JMComicDownloader()
    
    #获取ID（用户手动输入）
    # scan = downloader.get_scan()
    # comic_id = scan.get_comic_id()
    # 直接使用ID（用户手动输入）
    comic_id = input("请输入漫画ID：")
    
    # 获取漫画信息
    comic_info = downloader.get_comic_info(comic_id)
    if comic_info:
        print(f"漫画名称: {comic_info['title']}")
        print(f"作者: {comic_info['author']}")
        print(f"简介: {comic_info['description']}")
        print(f"封面: {comic_info['cover_url']}")

    else:
        print("未找到该漫画，请检查ID是否正确。")
        
    # 获取漫画章节列表
    chapters = downloader.get_chapters(comic_id)
    if chapters:
        print("章节列表:")
        for chapter in chapters:
            print(f"章节ID: {chapter['id']}, 章节名称: {chapter['title']}")
    else:
        print("未找到该漫画的章节列表。")
        
    # 下载漫画
    download_choice = input("是否下载漫画？(y/n): ")
    if download_choice.lower() == 'y':
        # 判断是否只有一章
        if len(chapters) == 1:
            print("该漫画只有一章，正在下载...")
            chapter_id = chapters[0]['id']
            chapter_title = chapters[0]['title']
            print(f"正在下载章节: {chapter_title} (ID: {chapter_id})")
            downloader.download_chapter(comic_id, chapter_id)
            # 将下载好的zip解压缩并将文件合并为pdf
            print(f"章节 {chapter_title} 下载完成！")
            print("正在解压缩并合并为PDF...")
            downloader.unzip_and_merge(comic_id, chapter_id)
            print(f"章节 {chapter_title} 解压缩并合并为PDF完成！")
        else:
            print("该漫画不是单行本，正在下载所有章节...")
            # 下载所有章节
            for chapter in chapters:
                chapter_id = chapter['id']
                chapter_title = chapter['title']
                print(f"正在下载章节: {chapter_title} (ID: {chapter_id})")
                downloader.download_chapter(comic_id, chapter_id)
                print(f"章节 {chapter_title} 下载完成！")
            # 将下载好的zip解压缩并将文件合并为pdf
            print("正在解压缩并合并为PDF...")
            for chapter in chapters:
                chapter_id = chapter['id']
                chapter_title = chapter['title']
                downloader.unzip_and_merge(comic_id, chapter_id)
                print(f"章节 {chapter_title} 解压缩并合并为PDF完成！")
        print("下载完成！")
    else:
        print("已取消下载。")
    
    
if __name__ == "__main__":
    main()
    