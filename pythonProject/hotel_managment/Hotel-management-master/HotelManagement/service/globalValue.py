# -*- coding: utf-8 -*-
from __future__ import unicode_literals
"""
用于跨文件修改的全局变量
"""
import sys
from dao.dbOpStaff import Staff
from dao.dbConfig import localSourceConfig as localConfig

"""员工信息的全局变量存取"""
def _initStaff():
    global staff
    staff = Staff()
    return staff

def get_staff():
    global staff
    return staff


















