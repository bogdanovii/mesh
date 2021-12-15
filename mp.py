import math
import json
class Setka:

    def __init__(self):

        #сетка лежит в координатах xStart xFinish
        #yStart yFinich
        #z будут координаты, соответствующие нашей фигуре
        import border_step_chyzlov_yacheek_setka
        #self.xStart = -50
        self.xFinish = 50

        self.yStart = -50
        self.yFinish = 50

        self.zStart = -50
        self.zFinish = 50

        #зададим шаг сетки вдоль каждой из осей x и y
        self.StepX = 15
        self.StepY = 15
        self.StepZ = 15

        #количество узлов вдоль каждой из осей
        #Количество узлов вдоль каждой оси, ну если все узлы на ось
        #спроецировать
        self.N_x = int(  abs(self.xStart - self.xFinish) / self.StepX ) + 1
        self.N_y = int(  abs(self.yStart - self.yFinish) / self.StepY ) + 1
        self.N_z = int(  abs(self.zStart - self.zFinish) / self.StepZ ) + 1
        #Следует понимать, что в это число узловв мы не вклюичли
        #Узел начала оси, поэтому общее число узлов:
        self.Number_of_nodes = (self.N_x )*(self.N_y )*(self.N_z )

        #создадим матрицу для хранения координт узлов
        # [x1ряд от оси х 1место,y,z1], [x1ряд2место,y2, z2], ...... [х 1 self.N_x , y ,zself.N_x]
        #[x2ряд1место, y1ряд2место,
        #пока не записали координаты, заполним ее нулями
        self.coord_of_Nodes = [0]
        for x in range(self.N_x):#у нас z слоев
            self.coord_of_Nodes.append(0)

        for x in range(self.N_x):#к каждому икс добавить игрек
            self.coord_of_Nodes[x] = [0]

        for x in range(self.N_x):#к каждому икс добавить игрек
            for y in range(self.N_y):
                self.coord_of_Nodes[x].append(0)

        for x in range(self.N_x):#от каждого икс игрека растим зед
            for y in range(self.N_y):
                self.coord_of_Nodes[x][y] = [0]
        for x in range(self.N_x):#от каждого икс игрека растим зед
            for y in range(self.N_y):
                for z in range(self.N_z):
                    self.coord_of_Nodes[x][y].append(0)

        #Итого имеем матирицу self.coord_of_Nodes[x][y][z]

        #заполним матрицу координт узлов:
        for x in range(self.N_x):#от каждого икс игрека растим зед
            for y in range(self.N_y):
                for z in range(self.N_z):
                    self.coord_of_Nodes[x][y][z] = [0, 0, 0]

        for x in range(self.N_x):#от каждого икс игрека растим зед
            for y in range(self.N_y):
                for z in range(self.N_z):
                    self.coord_of_Nodes[x][y][z] = [x * self.StepX, y * self.StepY, z * self.StepZ]

        #print(self.coord_of_Nodes)

        ########################################
        #Число ячеек
        self.Number_of_cells = (self.N_x - 1) * (self.N_y - 1) * (self.N_z - 1)




    def sdvig_v_sloe_XZ_coord_Z_do_ploskosti_Z(self, BoundLow_X, BoundUp_X, a, b, c, d):
        self.coord_of_Nodes_sdvig = self.coord_of_Nodes

        #будем говорить, что все должно быть плавно, то есть от обоих концов 7 грвдусов максиум
        #если наша плоскоть выходит за массив или это крайняя точка, то крайнюю не двигаем
        #ходим вперед назад, одну точку за раз можно только

        #узнаем, какие индексы лежат в нашем слое
        #проверка того, что слой ввобще как-то заходит



        #создадим шкалу которая закрашивает тру если точка уже двигалась
        lunki_X = [False]
        for x in range(self.N_x):#у нас z слоев
            lunki_X.append(False)

        for x in range(self.N_x):
            for z in range(self.N_z):
                for y in range(self.N_y):
                    for x in range(self.N_x):
                        for z in range(self.N_z):
                            for y in range(self.N_y):
                                #проверка того, что, сетка нах в слое
                                if self.coord_of_Nodes_sdvig[x][y][z][0] >= (BoundLow_X + self.StepX) and self.coord_of_Nodes_sdvig[x][y][z][0] < (BoundUp_X - self.StepX):
                                    #проверка того, что, не крайние по икс и зед и игрек
                                    if x != 0 and x != (self.N_x - 1) and z != 0 and z != (self.N_x - 1) and y != 0 and y != (self.N_x - 1):
                                        #смотрим плоскость выше или  неиже
                                        #поставляем икс и игрек координаты в уравнение плоскости и сравниваем зед
                                        z_plosk = (-d -a*self.coord_of_Nodes_sdvig[x][0][0][0] -b*self.coord_of_Nodes_sdvig[x][0][0][1]) / c

                                        #Узнаем на какое максимальное расстояние можно сдивнуть
                                        max_sdvig = z_plosk - self.coord_of_Nodes_sdvig[x][0][0][2]

                                        #ПРоверяем, что не крайние по зед
                                        #!!!!!!!!!!!!!!добваить

                                        #два случа сдвиг вниз и вверх
                                        #случай вверх
                                        if(max_sdvig >= 0):
                                            #измеряем расстояние до слеждущей координаты z
                                            if max_sdvig > (self.coord_of_Nodes_sdvig[x][0][0+1][2] - self.coord_of_Nodes_sdvig[x][0][0][2]):
                                                max_sdvig = (self.coord_of_Nodes_sdvig[x][0][0+1][2] - self.coord_of_Nodes_sdvig[x][0][0][2])
                                            #осталось урезать по процентам, чтобы это были малые углы справа и слева, выбираме где меньше
                                            #смотрим насколько можно поднять слева и справа выбтраем наименьшее и сравнпваем
                                            max_sdv_left = math.atan(7*3.1415/180)*(self.coord_of_Nodes_sdvig[x][0][0][0]-self.coord_of_Nodes_sdvig[x-1][0][0][0])
                                            max_sdv_right = math.atan(7*3.1415/180)*(self.coord_of_Nodes_sdvig[x+1][0][0][0]-self.coord_of_Nodes_sdvig[x][0][0][0])

                                            if max_sdvig > max_sdv_left:
                                                max_sdvig = max_sdv_left

                                            if max_sdvig > max_sdv_right:
                                                max_sdvig = max_sdv_right


                                        #вниз
                                        else:
                                            max_sdvig = abs(max_sdvig)
                                            #измеряем расстояние до слеждущей координаты z
                                            if max_sdvig > (self.coord_of_Nodes_sdvig[x][0][0][2] - self.coord_of_Nodes_sdvig[x][0][0-1][2]):
                                                max_sdvig = (self.coord_of_Nodes_sdvig[x][0][0][2] - self.coord_of_Nodes_sdvig[x][0][0-1][2])
                                                #осталось урезать по процентам, чтобы это были малые углы справа и слева, выбираме где меньше
                                                #смотрим насколько можно поднять слева и справа выбтраем наименьшее и сравнпваем
                                                max_sdv_left = math.atan(7*3.1415/180)*(self.coord_of_Nodes_sdvig[x][0][0][0]-self.coord_of_Nodes_sdvig[x-1][0][0][0])
                                                max_sdv_right = math.atan(7*3.1415/180)*(self.coord_of_Nodes_sdvig[x+1][0][0][0]-self.coord_of_Nodes_sdvig[x][0][0][0])

                                            if max_sdvig > max_sdv_left:
                                                max_sdvig = max_sdv_left

                                            if max_sdvig > max_sdv_right:
                                                max_sdvig = max_sdv_right

                                            max_sdvig = (-1) * max_sdvig


                                        #чтобы не было наложения
                                        max_sdvig = max_sdvig*0.999




                                        self.coord_of_Nodes_sdvig[x][0][0][2] = max_sdvig + self.coord_of_Nodes_sdvig[x][0][0][2]

        self.coord_of_Nodes = self.coord_of_Nodes_sdvig




class Printer:

    def __init__(self, setk):

        self.setka = setk

    def print_Paralepip(self):

        with open('MyX_Y_Z.vtk', 'w') as my_f:

            #vtk header:

            #vtk DataFile Version
            my_f.write('# vtk DataFile Version 3.0\n')

            #info about data
            my_f.write('Generated by mfem-seismo\n')

            #The file format
            my_f.write('ASCII\n')

            #dataset structure
            my_f.write('DATASET UNSTRUCTURED_GRID\n')


            #POINT_DATA n
            #Пишем число узлов наш втк файл

            my_f.write(' '.join(['POINTS', str(int(self.setka.Number_of_nodes)), 'double\n']))

            for x in range(self.setka.N_x):#от каждого икс игрека растим зед
                for y in range(self.setka.N_y):
                    for z in range(self.setka.N_z):
                        my_f.write(' '.join([str(self.setka.coord_of_Nodes[x][y][z][0]), str(self.setka.coord_of_Nodes[x][y][z][1]), str(self.setka.coord_of_Nodes[x][y][z][2]), '\n']))

            #CELL_DATA n
            #пишем ячейки: отмечаем, что будем писать ячейки, их количество
            #и количество точек ячейик, которыми она контачит
            #8 узлов + 1, 1 это  запись цифры 8
            my_f.write(' '.join(['CELLS', str(self.setka.Number_of_cells), str(9 * self.setka.Number_of_cells), '\n']))

            #Пронумеруем все грани ячеек, Внимание/, это тольок для куба работает
            self.Nymera_of_Nodes = [0]

            for x in range(self.setka.N_x):#у нас z слоев
                self.Nymera_of_Nodes.append(0)

            for x in range(self.setka.N_x):#к каждому икс добавить игрек
                self.Nymera_of_Nodes[x] = [0]

            for x in range(self.setka.N_x):#к каждому икс добавить игрек
                for y in range(self.setka.N_y):
                    self.Nymera_of_Nodes[x].append(0)

            for x in range(self.setka.N_x):#от каждого икс игрека растим зед
                for y in range(self.setka.N_y):
                    self.Nymera_of_Nodes[x][y] = [0]
            for x in range(self.setka.N_x):#от каждого икс игрека растим зед
                for y in range(self.setka.N_y):
                    for z in range(self.setka.N_z):
                        self.Nymera_of_Nodes[x][y].append(0)

            #Итого имеем матирицу self.Nymera_of_Nodes[x][y][z]

            #заполним матрицу координт узлов:
            for x in range(self.setka.N_x):#от каждого икс игрека растим зед
                for y in range(self.setka.N_y):
                    for z in range(self.setka.N_z):
                        self.Nymera_of_Nodes[x][y][z] = 0

            #кажой ячейки айди типа инт , начинающийся с нуля
            yacheika_id = 0
            for z in range(self.setka.N_z):
                for y in range(self.setka.N_y):
                    for x in range(self.setka.N_x):
                        self.Nymera_of_Nodes[x][y][z] = yacheika_id
                        yacheika_id = yacheika_id + 1

            #проверить равны ли yacheika_id и число точек
            #print('yacheika_id = ', yacheika_id)
            #print('self.Number_of_nodes = ', self.setka.Number_of_nodes)
            for z in range(self.setka.N_z-1):
                for y in range(self.setka.N_y-1):
                    for x in range(self.setka.N_x-1):
                        #print('8', end=' ')
                        my_f.write('8 ')
                        for zz in range(2):
                            for yy in range(2):
                                for xx in range(2):
                                    if xx < 1 or yy < 1 or zz < 1:
                                        #print(self.Nymera_of_Nodes[x + xx][y + yy][z + zz], end=' ')
                                        my_f.write(''.join([str(self.Nymera_of_Nodes[x + xx][y + yy][z + zz]), ' ']))
                                    else:
                                        #print(self.Nymera_of_Nodes[x + xx][y + yy][z + zz])
                                        my_f.write(' '.join([str(self.Nymera_of_Nodes[x + xx][y + yy][z + zz]), '\n']))


            my_f.write(' '.join(['CELL_TYPES', str(self.setka.Number_of_cells), '\n']))

            for _ in range(self.setka.Number_of_cells):
                my_f.write('12\n')

            my_f.write(' '.join(['CELL_DATA', str(self.setka.Number_of_cells), '\n']))

            my_f.write('SCALARS material int\n')
            my_f.write('LOOKUP_TABLE default\n')

            for _ in range(self.setka.Number_of_cells):
                my_f.write('1\n')





#############    main    #################
setka1 = Setka()
vtkPrint = Printer(setka1)
vtkPrint.print_Paralepip()


BoundLow_X = -40
BoundUp_X = 40
#ax + by +cz + d = 0
a = 0
b = 0
c = 1
d = -1000

setka1.sdvig_v_sloe_XZ_coord_Z_do_ploskosti_Z(BoundLow_X, BoundUp_X, a, b, c, d)

vtkPrint.print_Paralepip()
