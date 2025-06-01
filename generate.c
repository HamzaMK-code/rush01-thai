 /* ------------------------------------------------------------ *
 * ส่วนนี้ใช้สร้างความเป็นไปได้ทั้งหมดของแถวในตาราง 4x4      *
 * แต่ละแถวต้องมีเลขไม่ซ้ำกัน: 1, 2, 3, 4                     *
 * → เราจึงต้องสร้างชุดเรียงสลับทั้งหมดของ [1, 2, 3, 4]       *
 * จะมีทั้งหมด 24 แบบที่ไม่ซ้ำกัน (4!)                         *
 ****************************************************************/

// บันทึกชุดข้อมูลที่ valid (หลังจากตรวจสอบว่าไม่ซ้ำ)
void store_perm(int combo[4], int *p, int values[4], int perms[24][4])
{
    if (*p < 24) // จำกัดแค่ 24 permutations เท่านั้น
    {
        // แปลงจาก index เป็นค่าจริง {1, 2, 3, 4}
        perms[*p][0] = values[combo[0]];
        perms[*p][1] = values[combo[1]];
        perms[*p][2] = values[combo[2]];
        perms[*p][3] = values[combo[3]];
        (*p)++; // เพิ่มตำแหน่งถัดไป
    }
}

// ตรวจสอบว่า combo มีเลขไม่ซ้ำ แล้วค่อยบันทึก
void check_and_store(int combo[4], int *p, int values[4], int perms[24][4])
{
    // ตรวจสอบว่า index ทั้ง 4 ไม่ซ้ำกัน
    if (combo[0] != combo[1] && combo[0] != combo[2] && combo[0] != combo[3]
        && combo[1] != combo[2] && combo[1] != combo[3] && combo[2] != combo[3])
        store_perm(combo, p, values, perms); // ถ้าผ่าน ให้เก็บไว้
}

// ลูปเพื่อสร้างชุดตัวเลข 4 ตัวที่เป็นไปได้ทั้งหมด
void generate_perms_loops_2(int a, int *p, int values[4], int perms[24][4])
{
    int b;
    int c;
    int d;
    int combo[4]; // เก็บตำแหน่ง index 4 ตัว

    b = -1;
    while (++b < 4)
    {
        c = -1;
        while (++c < 4)
        {
            d = -1;
            while (++d < 4)
            {
                // สร้าง combo 4 ตัว
                combo[0] = a;
                combo[1] = b;
                combo[2] = c;
                combo[3] = d;
                // ตรวจสอบและเก็บถ้าผ่าน
                check_and_store(combo, p, values, perms);
            }
        }
    }
}

// ลูปตัวแรกสำหรับตำแหน่งแรก แล้วเรียกฟังก์ชันย่อยต่อ
void generate_perms_loops(int values[4], int perms[24][4])
{
    int a;
    int p;

    p = 0;   // ตัวนับจำนวน permutations ที่เก็บไว้
    a = -1;
    while (++a < 4)
        generate_perms_loops_2(a, &p, values, perms); // เรียกลูปย่อย
}

// เริ่มสร้าง permutations จากค่าตั้งต้น {1, 2, 3, 4}
void generate_perms(int perms[24][4])
{
    int values[4];

    values[0] = 1;
    values[1] = 2;
    values[2] = 3;
    values[3] = 4;
    generate_perms_loops(values, perms); // เติม perms ด้วยแถวที่ valid ทั้งหมด
}
