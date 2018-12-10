object frmSetIni: TfrmSetIni
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu]
  Caption = #37197#32622
  ClientHeight = 157
  ClientWidth = 339
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object lbl1: TLabel
    Left = 48
    Top = 20
    Width = 82
    Height = 13
    Caption = #39057#35889#20202'IP'#22320#22336#65306
  end
  object lbl2: TLabel
    Left = 58
    Top = 50
    Width = 72
    Height = 13
    Caption = #28369#21488#20018#21475#21495#65306
  end
  object lbl3: TLabel
    Left = 22
    Top = 80
    Width = 108
    Height = 13
    Caption = #28369#21488#31227#21160#26368#23567#36317#31163#65306
  end
  object edt_IP: TEdit
    Left = 144
    Top = 17
    Width = 121
    Height = 21
    TabOrder = 0
  end
  object edt_Port: TEdit
    Left = 144
    Top = 47
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object btn_OK: TButton
    Left = 64
    Top = 112
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 2
    OnClick = btn_OKClick
  end
  object btn_Cancel: TButton
    Left = 176
    Top = 112
    Width = 75
    Height = 25
    Caption = 'Cancel'
    TabOrder = 3
    OnClick = btn_CancelClick
  end
  object cbb_SingleLen: TComboBox
    Left = 144
    Top = 77
    Width = 121
    Height = 21
    TabOrder = 4
    OnKeyPress = cbb_SingleLenKeyPress
    Items.Strings = (
      '5'
      '10'
      '20'
      '30'
      '40'
      '50')
  end
end
