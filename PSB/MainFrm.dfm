object frmMain: TfrmMain
  Left = 549
  Top = 154
  Caption = 'frmMain'
  ClientHeight = 616
  ClientWidth = 970
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -14
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 14
  object pnl1: TPanel
    Left = 0
    Top = 0
    Width = 970
    Height = 129
    Align = alTop
    TabOrder = 0
    object lbl16: TLabel
      Left = 32
      Top = 27
      Width = 70
      Height = 14
      Caption = #26465#30721#32534#21495#65306
    end
    object btn1: TButton
      Left = 384
      Top = 23
      Width = 97
      Height = 25
      Caption = #19968#38190#26816#27979
      TabOrder = 0
      OnClick = btn1Click
    end
    object edt15: TEdit
      Left = 116
      Top = 24
      Width = 205
      Height = 22
      TabOrder = 1
    end
    object btn2: TButton
      Left = 664
      Top = 40
      Width = 75
      Height = 25
      Caption = 'btn2'
      TabOrder = 2
      OnClick = btn2Click
    end
  end
  object pnl2: TPanel
    Left = 0
    Top = 129
    Width = 970
    Height = 487
    Align = alClient
    TabOrder = 1
    object grpbx1: TGroupBox
      Left = 17
      Top = 6
      Width = 425
      Height = 435
      Caption = #26368#23567#36755#20837#30005#21387
      TabOrder = 0
      object lbl8: TLabel
        Left = 27
        Top = 47
        Width = 35
        Height = 14
        Caption = '110V:'
      end
      object lbl1: TLabel
        Left = 27
        Top = 86
        Width = 35
        Height = 14
        Caption = '110V:'
      end
      object lbl2: TLabel
        Left = 27
        Top = 125
        Width = 28
        Height = 14
        Caption = '24V:'
      end
      object lbl3: TLabel
        Left = 27
        Top = 167
        Width = 28
        Height = 14
        Caption = '24V:'
      end
      object lbl4: TLabel
        Left = 27
        Top = 210
        Width = 21
        Height = 14
        Caption = '5V:'
      end
      object lbl5: TLabel
        Left = 27
        Top = 252
        Width = 35
        Height = 14
        Caption = '3.3V:'
      end
      object lbl6: TLabel
        Left = 27
        Top = 295
        Width = 35
        Height = 14
        Caption = '1.2V:'
      end
      object lbl18: TLabel
        Left = 31
        Top = 336
        Width = 63
        Height = 14
        Caption = '24V 1'#36335#65306
      end
      object lbl19: TLabel
        Left = 31
        Top = 364
        Width = 63
        Height = 14
        Caption = '24V 2'#36335#65306
      end
      object lbl20: TLabel
        Left = 235
        Top = 47
        Width = 119
        Height = 14
        Caption = '(104.5V ~ 115.5V)'
      end
      object lbl21: TLabel
        Left = 235
        Top = 86
        Width = 119
        Height = 14
        Caption = '(104.5V ~ 115.5V)'
      end
      object lbl22: TLabel
        Left = 235
        Top = 125
        Width = 105
        Height = 14
        Caption = '(23.8V ~ 25.2V)'
      end
      object lbl23: TLabel
        Left = 235
        Top = 167
        Width = 105
        Height = 14
        Caption = '(23.8V ~ 25.2V)'
      end
      object lbl24: TLabel
        Left = 235
        Top = 210
        Width = 105
        Height = 14
        Caption = '(4.75V ~ 5.25V)'
      end
      object lbl25: TLabel
        Left = 235
        Top = 252
        Width = 119
        Height = 14
        Caption = '(3.135V ~ 3.465V)'
      end
      object lbl26: TLabel
        Left = 235
        Top = 295
        Width = 105
        Height = 14
        Caption = '(1.14V ~ 1.26V)'
      end
      object edt1: TEdit
        Left = 102
        Top = 44
        Width = 67
        Height = 22
        TabOrder = 0
      end
      object edt2: TEdit
        Left = 102
        Top = 83
        Width = 67
        Height = 22
        TabOrder = 1
      end
      object edt3: TEdit
        Left = 102
        Top = 122
        Width = 67
        Height = 22
        TabOrder = 2
      end
      object edt4: TEdit
        Left = 102
        Top = 164
        Width = 67
        Height = 22
        TabOrder = 3
      end
      object edt5: TEdit
        Left = 102
        Top = 207
        Width = 67
        Height = 22
        TabOrder = 4
      end
      object edt6: TEdit
        Left = 102
        Top = 249
        Width = 67
        Height = 22
        TabOrder = 5
      end
      object edt7: TEdit
        Left = 102
        Top = 292
        Width = 67
        Height = 22
        TabOrder = 6
      end
      object edt20: TEdit
        Left = 121
        Top = 333
        Width = 69
        Height = 22
        TabOrder = 7
      end
      object edt21: TEdit
        Left = 211
        Top = 333
        Width = 69
        Height = 22
        TabOrder = 8
      end
      object edt22: TEdit
        Left = 211
        Top = 361
        Width = 69
        Height = 22
        TabOrder = 9
      end
      object edt23: TEdit
        Left = 121
        Top = 361
        Width = 69
        Height = 22
        TabOrder = 10
      end
    end
    object grpbx2: TGroupBox
      Left = 448
      Top = 6
      Width = 350
      Height = 459
      Caption = #26368#22823#36755#20837#30005#21387
      TabOrder = 1
      object lbl7: TLabel
        Left = 47
        Top = 336
        Width = 63
        Height = 14
        Caption = '24V 1'#36335#65306
      end
      object lbl9: TLabel
        Left = 47
        Top = 47
        Width = 35
        Height = 14
        Caption = '110V:'
      end
      object lbl10: TLabel
        Left = 47
        Top = 86
        Width = 35
        Height = 14
        Caption = '110V:'
      end
      object lbl11: TLabel
        Left = 47
        Top = 125
        Width = 28
        Height = 14
        Caption = '24V:'
      end
      object lbl12: TLabel
        Left = 47
        Top = 167
        Width = 28
        Height = 14
        Caption = '24V:'
      end
      object lbl13: TLabel
        Left = 47
        Top = 210
        Width = 21
        Height = 14
        Caption = '5V:'
      end
      object lbl14: TLabel
        Left = 47
        Top = 252
        Width = 35
        Height = 14
        Caption = '3.3V:'
      end
      object lbl15: TLabel
        Left = 47
        Top = 295
        Width = 35
        Height = 14
        Caption = '1.2V:'
      end
      object lbl17: TLabel
        Left = 47
        Top = 364
        Width = 63
        Height = 14
        Caption = '24V 2'#36335#65306
      end
      object edt8: TEdit
        Left = 119
        Top = 44
        Width = 69
        Height = 22
        TabOrder = 0
      end
      object edt9: TEdit
        Left = 119
        Top = 83
        Width = 69
        Height = 22
        TabOrder = 1
      end
      object edt10: TEdit
        Left = 119
        Top = 122
        Width = 69
        Height = 22
        TabOrder = 2
      end
      object edt11: TEdit
        Left = 119
        Top = 164
        Width = 69
        Height = 22
        TabOrder = 3
      end
      object edt12: TEdit
        Left = 119
        Top = 207
        Width = 69
        Height = 22
        TabOrder = 4
      end
      object edt13: TEdit
        Left = 119
        Top = 249
        Width = 69
        Height = 22
        TabOrder = 5
      end
      object edt14: TEdit
        Left = 119
        Top = 292
        Width = 69
        Height = 22
        TabOrder = 6
      end
      object edt16: TEdit
        Left = 137
        Top = 333
        Width = 69
        Height = 22
        TabOrder = 7
      end
      object edt17: TEdit
        Left = 240
        Top = 333
        Width = 69
        Height = 22
        TabOrder = 8
      end
      object edt18: TEdit
        Left = 137
        Top = 361
        Width = 69
        Height = 22
        TabOrder = 9
      end
      object edt19: TEdit
        Left = 240
        Top = 361
        Width = 69
        Height = 22
        TabOrder = 10
      end
    end
    object StatusBar1: TStatusBar
      Left = 1
      Top = 467
      Width = 968
      Height = 19
      Panels = <>
    end
  end
end
