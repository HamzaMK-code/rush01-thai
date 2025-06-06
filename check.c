/***************************************************************
 *                 ฟังก์ชันตรวจสอบความถูกต้องของตาราง         *
 * ------------------------------------------------------------ *
 * ฟังก์ชันเหล่านี้ใช้เพื่อตรวจสอบว่าตาราง 4x4 ที่สร้างขึ้น   *
 * ปฏิบัติตามกฎของเกมหรือไม่:                                 *
 *                                                             *
 * 1. ต้องตรงกับเบาะแสทั้ง 16 ด้านที่ให้ไว้รอบตาราง            *
 *    → เบาะแสบอกจำนวนตึกที่สามารถมองเห็นจากแต่ละด้าน         *
 *      (บน, ล่าง, ซ้าย, ขวา)                                 *
 * 2. คอลัมน์แต่ละช่องต้องไม่มีค่าซ้ำกัน                      *
 *                                                             *
 * ตารางประกอบด้วยเลข 1 ถึง 4 (แทนความสูงของตึก)             *
 * แถวและคอลัมน์แต่ละชุดต้องมีเลข 1, 2, 3, 4 เพียงครั้งเดียว *
 ***************************************************************/

int count_visible(int *line)
{
    int max;
    int count;
    int i;

    i = 0;
    max = 0;      // เริ่มต้นด้วยตึกที่สูงสุดเป็น 0
    count = 0;    // จำนวนตึกที่มองเห็นได้
    while (i < 4)
    {
        if (line[i] > max) // ถ้าตึกนี้สูงกว่าตึกที่เคยเจอ
        {
            max = line[i]; // ปรับค่าตึกที่สูงที่สุด
            count++;       // เห็นตึกนี้ เพิ่ม count
        }
        i++;
    }
    return (count); // ส่งกลับจำนวนตึกที่มองเห็น
}

// นับจำนวนตึกที่มองเห็นจากขวาไปซ้าย
// เพียงแค่กลับลำดับแถว แล้วเรียก count_visible()
int reverse_count(int *line)
{
    int rev[4];
    int i;

    i = 0;
    while (i < 4)
    {
        rev[i] = line[3 - i]; // คัดลอกลำดับจากขวาไปซ้าย
        i++;
    }
    return (count_visible(rev)); // ใช้ฟังก์ชันเดิมกับแถวที่กลับด้านแล้ว
}

// ตรวจสอบว่าตาราง 4x4 ตรงกับเบาะแสทั้ง 16 จุดหรือไม่
int check_clues(int grid[4][4], int *clues)
{
    int col[4];
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        // ตรวจสอบจากซ้ายไปขวาในแถว i
        if (count_visible(grid[i]) != clues[8 + i])
            return (0);
        // ตรวจสอบจากขวาไปซ้ายในแถว i
        if (reverse_count(grid[i]) != clues[12 + i])
            return (0);

        // สร้างคอลัมน์ i ด้วยมือ
        j = 0;
        while (j < 4)
        {
            col[j] = grid[j][i]; // สร้างคอลัมน์จากแถว
            j++;
        }

        // ตรวจสอบจากบนลงล่างในคอลัมน์ i
        if (count_visible(col) != clues[i])
            return (0);
        // ตรวจสอบจากล่างขึ้นบนในคอลัมน์ i
        if (reverse_count(col) != clues[4 + i])
            return (0);

        i++;
    }
    return (1); // ถ้าทุกเงื่อนไขผ่าน
}

// ตรวจสอบว่าทุกคอลัมน์ไม่มีเลขซ้ำกัน
int check_all_cols(int grid[4][4])
{
    int c;   // ดัชนีคอลัมน์
    int r1;  // แถวแรกที่จะเปรียบเทียบ
    int r2;  // แถวที่สองที่จะเปรียบเทียบ

    c = 0;
    while (c < 4)
    {
        r1 = 0;
        while (r1 < 4)
        {
            r2 = r1 + 1;
            while (r2 < 4)
            {
                if (grid[r1][c] == grid[r2][c]) // ถ้ามีเลขซ้ำในคอลัมน์เดียวกัน
                    return (0); // ไม่ผ่าน
                r2++;
            }
            r1++;
        }
        c++;
    }
    return (1); // คอลัมน์ทั้งหมดผ่าน
}
