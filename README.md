# Fireboy and Watergirl Adventure 
- Họ và tên: Bùi Trung Thanh 
- Lớp K68J, Trường Đại học Công Nghệ, Đại học Quốc gia Hà Nội (UET - VNU)

# Video Demo

# Table Of Content
- [**Fireboy and Watergirl**](#Fireboy-and-Watergirl-Adventure)
    - [**Video Demo**](#Video-demo)
    - [***Table Of Contents***](#Table-Of-Contents)
    - [***Cách tải game***](#Cách-tải-gamegame)
    - [**Giới thiệu game**](#Giới-thiệu-game)
    - [**Hướng dẫn chơi**](#Hướng-dẫn-chơi)
    - [**Các thành phần trong game**](#Các-thành-phần-trong-game)
    - [**Chiến thắng và thất bại**](#Chiến-thắng-và-thất-bại )
    - [**Cấu trúc game**](#Cấu-trúc-game)
    - [**Về đồ họa**](#Về-đồ-họa)
    - [**Nguồn tham khảo**](#Nguồn-tham-khảo)
# Giới thiệu game 
- Fireboy and Watergirl Adventure là một trò chơi dành cho 2 người, phối hợp đơn giản. Bạn chỉ có thể qua màn một khi hai nhân vật cùng tới đích.
- Nhân vật chính trong game là Fireboy (chú bé lửa) và Watergirl (cô bé nước). Hai nhân vật này bị mắc kẹt trong một mê cung. Để thoát ra được, họ phải trải qua rất nhiều thử thách khó khăn và thú vị. 
- Hãy rủ bạn bè của mình cùng hóa thân vào hai nhân vật này để có những giây phút thoải mái nhé.

# Cách tải game 
## Cách 1: Không bao gồm code
- Tải game (được nén thành file .zip) tại [đây](https://github.com/tbui9887/fireboy-and-watergirl/releases/download/release/fireboy-and-watergirl.zip)
- File zip này khoảng 36 MB nên thời gian tải rất nhanh 
- Sau khi giải nén, file chỉ chiếm khoảng 75 MB
## Cách 2: Bao gồm code
### 1. Clone trên github
- Nếu trong máy bạn cài sẵn Code::Blocks bạn chỉ cần git về, sau đó vào file `bin` → `Debug`, sau đó bạn click vào file `.exe`để chạy game như bình thường 
- Tuy nhiên cách này sẽ tải cả phần `.git` nên file sẽ khá nặng
## Cách 2: Tải file `.zip`
- Click vào `Code` màu xanh ở phần phía trên 
- Sau đó bạn nhấn vào `Download ZIP`
- File này sẽ nhẹ hơn phía trên, tùy theo mục đích của bạn để lựa chọn phương thức tải cho phù hợp 
# Hướng dẫn chơi 
## Đối với người điều khiển Watergirl 
- Sử dụng phím `a` để di chuyển sang trái
- Sử dụng phím `d` để di chuyển sang phái 
- Sử dụng phím `w` để nhảy lên trên
- Sử dụng phím `q` để đặt bom
 
## Đối với người điều khiển Fireboy 
- Sử dụng phím `←` để di chuyển sang trái
- Sử dụng phím `→` để di chuyển sang phải
- Sử dụng phím `↑` để nhảy lên trên
- Sử dụng phím `l` để đặt bom

# Các thành phần trong game 
## Nhân vật chính
### Fireboy
![Link ảnh Fireboy](Data/readme_photo/fireboy.png)
- Bạn sẽ điều khiển nhân vật này để đi tới cửa của mình (cửa có kí hiệu màu cam) 
### Watergirl
![Link ảnh Watergirl](Data/readme_photo/watergirl.png)
- Một người chơi khác sẽ điều khiển nhân vật này, mục tiêu cuối cùng cũng như Fireboy (cửa có kí hiệu màu xanh)
- Hãy cố gắng phối hợp với nhau thật tốt, đừng bỏ quên bạn bè mà đi một mình nhé, vì chưa chắc một mình đã có thể qua cửa đâu 
## Các object tương tác với người chơi 
### Slime
![Link ảnh Slime](Data/readme_photo/slime.png)
- Slime sẽ liên tục di chuyển trong suốt quá trình chơi, việc của bạn là tránh đụng vào nó, nếu không nhân vật của bạn sẽ chết 
- Bạn sẽ thua cuộc khi chạm, dù chỉ một chút với Slime. 
### Barrier và button 
![Link ảnh Barrier](Data/photo/block/barrier_blue.png)
- Barrier là một thanh chắn có thể di chuyển được. Nếu nhân vật mà bạn của bạn điều khiển không đứng trên nút thì Barrier sẽ không di chuyển lên trên, bạn sẽ bị chắn và không thể đi qua được

![Link ảnh Button](Data/photo/block/button_blue.png)
- Như đã đề cập ở trên, khi nhân vật của bạn đứng trên button, thanh chắn Barrier của bạn sẽ di chuyển và bạn của bạn có thể đi qua được nó
### Bomb
![Linh ảnh Bomb](Data/readme_photo/bomb.png)
- Bomb sẽ nổ sau 2 giây sau khi bắt đầu đặt.
- Tuy nhiên với mỗi một nhân vật, bạn chỉ có thể đặt lại một quả bom nữa chỉ khi đã qua 30 giây kể từ lần đặt gần nhất. 
### Thời gian chơi 
![Link thời gian chơi](Data/readme_photo/time.png)
- Thời gian sẽ hiện ở chính giữa của màn hình chơi.
- Thời gian sẽ quyết định xem bạn ở đó được bao lâu. Hãy cố gắng nhanh nhất có thể vì càng về sau sẽ càng đuối sức đấy nhé. 
### Kim cương
![Kim cương](Data/readme_photo/yellow_coin.png)
![Kim cương](Data/readme_photo/blue_coin.png)
- Hãy cố gắng ăn thật nhiều kim cương để khi qua cửa có thể dành được số điểm cao nhất.
- Nhớ rằng, bạn chỉ có thể ăn được khi ăn đúng với nhân vật của mình: Fireboy ăn kim cương vàng, Watergirl ăn kim cương xanh.
### Hồ dung nham 
![Ho dung nham](Data/readme_photo/lava_liquid.png)
- Fireboy có thể đi qua được hồ này mà không bị làm sao cả, trong khi đó Watergirl sẽ bốc hơi khi đắm mình trong đó.
### Hồ nước lạnh 
![Ho nuoc lanh](Data/readme_photo/water_liquid.png)
- Tương tự như vậy, Watergirl có thể đi qua được hồ nước, nhưng Fireboy thì không thể đi qua được.
### Hồ axit 
![Ho axit](Data/readme_photo/toxic_liquid.png)
- Hồ axit vô cùng độc hại, cả hai nhân vật đều không thể đi qua được chỗ này.
- Nếu một nhân vật bị rơi xuống đây, cả hai đều sẽ bị thua cuộc.
# Chiến thắng và thất bại 
## Chiến thắng
![Hinh chien thang](Data/readme_photo/winning_menu.png)
- Có 4 cấp độ đánh giá khi bạn chiến thắng: `A`, `B`, `C`, `D`
- Bạn đạt được `A`, khi hoàn thành tất cả những điều kiện đặt ra của trò chơi
- Bạn đạt được `B`, khi không hoàn thành được 1 điều kiện.
- Bạn đạt được `C`, khi không hoàn thành 2 điều kiện.
- Bạn đạt được `D`, khi không hoàn thành một điều kiện nào

## Thất bại 
![Hinh thua cuoc](Data/readme_photo/losing_menu.png)
- Khi thất bại, dù bạn có `Pass` tất cả các điều kiện thì bạn vẫn chỉ nhận được `F` mà thôi.

- Tại đây bạn có thể bấm vào icon hình ngôi nhà để đi ra màn hình chính, bấm vào nút quay lại để chơi lại. Trong cả màn hình thắng và thua đều có 2 icon này để bạn lựa chọn.

# Kĩ thuật lập trình 
## Phát triển trên nền tảng
- IDE Code::Blocks 20.03
- Ngôn ngữ lập trình C++
- Thư viện SDL2 
- Extension của SDL2:
	- SDL_Image: Hỗ trợ xử lý hình ảnh 
	- SDL_Mixer: Hỗ trợ xử lý âm thanh
	- SDL_TTF: Hỗ trợ xử lý font

## Các kĩ thuật lập trình
- Vòng lặp, cấu trúc rẽ nhánh,...
- Con trỏ, vector, string,...
- Class, struct, kế thừa, hàm ảo,...
- Đọc viết file: fstream
- Tách file quản lý code
- Kỹ thuật duyệt mảng, sinh số ngẫu nhiên
- Các kĩ thuật, syntax của SDL
- Kĩ thuật giải phóng bộ nhớ
- Kĩ thuật xử lý thời gian 

# Về source code game
- File header.h
    - Khai báo các thư viện có sẵn trong C++, SDL2
    - Các define sử dụng trong các hàm 
    - Các thông số cố định sử dụng trong game 
- File character: tương tác map, tương tác với các thành phần đặc biệt của map, xử lý event, load ảnh, load audio,...
- File game_map: truyền dữ liệu từ file vào trong game, load map tiles
- File enemy: tương tác map, tương tác với nhân vật người chơi điều khiển, load ảnh, tính toán vị trí mới khi vị trí khởi đầu và vị trí kết thúc không hợp lý,...
- File select_menu: toàn bộ các hàm xử lý liên quan tới menu, load các thành phần ban đầu khi khởi động màn mới của game 
- Các file texture, timer, text: các thành phần cơ bản để load ảnh lên, xử lý thời gian, tạo text cho game
    - File texture bao gồm class LTexture làm class cha để class MainObject, Enemy,.. kế thừa 
- Hàm bomb: xử lý thời gian nổ, xử lý khi va chạm với nhân vật mà người chơi điều khiển và enemy, tương tác map, hiện thông báo khi chưa đủ thời gian đặt bom,...
- File object_button: xử lý khi va chạm với button thì barrier sẽ đi lên để cho nhân vật người chơi điều khiển có thể đi qua 
# Về đồ họa 
- Các texture trong game được lấy từ:
	- Map [itch.io](https://itch.io/)
	- Hình ảnh nhân vật [sanderfrenken.github.io](https://sanderfrenken.github.io/Universal-LPC-Spritesheet-Character-Generator/#?body=Body_color_light&head=Human_male_light)
	- Hình ảnh Slime [itch.io](https://itch.io/)
	- Hình ảnh Background [freepik.com](https://www.freepik.com/premium-vector/pixel-art-landscape-farm-coast-with-house-barn-silo-mill-8bit-game-background_31399610.htm)
	- Âm thanh soundtrack và music sound [downloads.khinider.com](https://downloads.khinsider.com/game-soundtracks/album/fireboy-and-watergirl)
- Các hình ảnh còn lại là bản thân mình tự làm sao cho phù hợp với game
- Vẽ tile map bằng phần mềm: [Tiled](https://www.mapeditor.org/)

# Nguồn tham khảo 

- Các syntax SDL cơ bản: [Lazyfoo](https://lazyfoo.net/tutorials/SDL/)
- Map, character: [Phát Triển Phần Mềm 123A-Z](https://www.youtube.com/@PhatTrienPhanMem123AZ)