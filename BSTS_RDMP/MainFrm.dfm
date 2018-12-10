object frmMain: TfrmMain
  Left = 411
  Top = 77
  Caption = #36752#23556#26816#27979#24037#20855
  ClientHeight = 604
  ClientWidth = 1049
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = mnmn1
  OldCreateOrder = False
  Position = poDesigned
  OnClose = FormClose
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object pnl_Canves: TPanel
    Left = 0
    Top = 145
    Width = 1049
    Height = 440
    Align = alClient
    TabOrder = 0
    object img_Frame: TImage
      Left = 1
      Top = 1
      Width = 1047
      Height = 438
      Align = alClient
      OnMouseDown = img_FrameMouseDown
      OnMouseMove = img_FrameMouseMove
      OnMouseUp = img_FrameMouseUp
      ExplicitWidth = 880
      ExplicitHeight = 583
    end
  end
  object pnl_Domain: TPanel
    Left = 0
    Top = 0
    Width = 1049
    Height = 145
    Align = alTop
    TabOrder = 1
    object grpbx1: TGroupBox
      Left = 1
      Top = 1
      Width = 1047
      Height = 66
      Align = alTop
      Caption = #33719#21462#36752#23556#20540
      TabOrder = 0
      object lbl_MaxDistance: TLabel
        Left = 5
        Top = 29
        Width = 60
        Height = 13
        Caption = #26368#22823#36317#31163#65306
      end
      object lbl_bAspect: TLabel
        Left = 188
        Top = 29
        Width = 36
        Height = 13
        Caption = #26041#21521#65306
        Color = clBtnFace
        ParentColor = False
      end
      object lbl1: TLabel
        Left = 384
        Top = 29
        Width = 36
        Height = 13
        Caption = #39057#29575#65306
        Color = clBtnFace
        ParentColor = False
      end
      object edt_MaxDistance: TEdit
        Left = 69
        Top = 26
        Width = 100
        Height = 21
        MaxLength = 4
        TabOrder = 0
        OnKeyPress = edt_MaxDistanceKeyPress
      end
      object btn_Start: TButton
        Left = 575
        Top = 18
        Width = 84
        Height = 33
        Caption = #21551#21160
        TabOrder = 3
        OnClick = btn_StartClick
      end
      object cbb_bAspect: TComboBox
        Left = 254
        Top = 26
        Width = 99
        Height = 21
        TabOrder = 1
        OnKeyPress = cbb_bAspectKeyPress
        Items.Strings = (
          #24038#21521
          #21491#21521)
      end
      object btn_pause: TButton
        Left = 686
        Top = 18
        Width = 83
        Height = 33
        Caption = #26242#20572
        TabOrder = 4
        OnClick = btn_pauseClick
      end
      object cbb_bRate: TComboBox
        Left = 449
        Top = 26
        Width = 99
        Height = 21
        TabOrder = 2
        OnKeyPress = cbb_bAspectKeyPress
        Items.Strings = (
          '1000'
          '2000'
          '3000')
      end
    end
    object grpbx2: TGroupBox
      Left = 1
      Top = 67
      Width = 1047
      Height = 66
      Align = alTop
      Caption = #31227#21160#28369#21488
      TabOrder = 1
      object lbl_MoveDistance: TLabel
        Left = 5
        Top = 27
        Width = 60
        Height = 13
        Caption = #31227#21160#36317#31163#65306
      end
      object lbl_Rate: TLabel
        Left = 384
        Top = 27
        Width = 36
        Height = 13
        Caption = #39057#29575#65306
        Color = clBtnFace
        ParentColor = False
      end
      object lbl_Aspect: TLabel
        Left = 189
        Top = 27
        Width = 36
        Height = 13
        Caption = #26041#21521#65306
        Color = clBtnFace
        ParentColor = False
      end
      object edt_MoveDistance: TEdit
        Left = 70
        Top = 24
        Width = 99
        Height = 21
        MaxLength = 4
        TabOrder = 0
        OnKeyPress = edt_MaxDistanceKeyPress
      end
      object cbb_Rate: TComboBox
        Left = 449
        Top = 24
        Width = 99
        Height = 21
        TabOrder = 2
        OnKeyPress = cbb_bAspectKeyPress
        Items.Strings = (
          '100'
          '500'
          '1000'
          '2000'
          '3000'
          '4000'
          '5000')
      end
      object btn_Send: TButton
        Left = 575
        Top = 19
        Width = 84
        Height = 33
        Caption = #21457#36865
        TabOrder = 3
        OnClick = btn_SendClick
      end
      object cbb_Aspect: TComboBox
        Left = 254
        Top = 24
        Width = 99
        Height = 21
        TabOrder = 1
        OnKeyPress = cbb_bAspectKeyPress
        Items.Strings = (
          #24038#21521
          #21491#21521)
      end
      object btn_stop: TButton
        Left = 686
        Top = 19
        Width = 83
        Height = 33
        Caption = #20572#27490
        TabOrder = 4
        OnClick = btn_stopClick
      end
    end
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 585
    Width = 1049
    Height = 19
    Color = clRed
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    Panels = <
      item
        Width = 50
      end>
    UseSystemFont = False
  end
  object tmr_B: TTimer
    Enabled = False
    OnTimer = tmr_BTimer
    Left = 988
    Top = 16
  end
  object mnmn1: TMainMenu
    BiDiMode = bdLeftToRight
    ParentBiDiMode = False
    Left = 1028
    Top = 16
    object N1: TMenuItem
      Caption = #25171#24320
      object mntmN6: TMenuItem
        Caption = #39057#35889#20202
        OnClick = mntmN6Click
      end
      object mntmN7: TMenuItem
        Caption = #20018#21475
        OnClick = mntmN7Click
      end
    end
    object N2: TMenuItem
      Caption = #20851#38381
      OnClick = N2Click
    end
    object mntmN4: TMenuItem
      Caption = #28165#31354
      OnClick = mntmN4Click
    end
    object mntmN3: TMenuItem
      Caption = #23548#20986
      OnClick = mntmN3Click
    end
    object N3: TMenuItem
      Caption = #22522#20934#32447
      object mntmN_Add: TMenuItem
        Caption = #28155#21152
        OnClick = mntmN_AddClick
      end
      object mntmN_Delete: TMenuItem
        Caption = #21024#38500
        OnClick = mntmN_AddClick
      end
    end
    object mntmN5: TMenuItem
      Caption = #35774#32622
      OnClick = mntmN5Click
    end
  end
end
