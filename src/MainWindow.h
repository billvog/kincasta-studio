#pragma once

#include <algorithm>

#include <QMainWindow>
#include <QDebug>
#include <QStyle>
#include <QStandardPaths>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QMimeData>
#include <QFile>
#include <QStandardItemModel>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsDropShadowEffect>
#include <QMediaPlayer>
#include <QInputDialog>

#include "AppInfo.h"
#include "AboutDialog.h"
#include "SubtitleTextHighlighter.h"
#include "SubtitleItem.h"
#include "SubParser.h"
#include "UndoItem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

protected:
	void closeEvent(QCloseEvent *e);
	void resizeEvent(QResizeEvent *);

	void dragEnterEvent(QDragEnterEvent *e);
	void dropEvent(QDropEvent *e);

	void keyPressEvent(QKeyEvent *event);

private:
	Ui::MainWindow *ui;

	SubtitleTextHighlighter *subtitlesTextHighlighter;

	QString SubFilePath;

	const QString SubtitleFileSelector = "Subtitle Files (*.srt *.vtt)";
	const QString MediaFileSelector = "Media Files (*.mp4 *.mpeg *.mkv *.webm *.avi *.flv *.mov *.vob *.ogv);;All Files (*.*)";
	bool hasFileOpen = false;
	bool isSaved = false;

	QList<SubtitleItem> Subtitles;
	int PrevEditinSubtitleIndex = -1;
	int EditingSubtitleIndex = -1;
	bool isSubApplied = true;

	QList<UndoItem> UndoItems;
	QList<UndoItem> RedoItems;

	QStandardItemModel *subtitlesModel;

	QGraphicsVideoItem *videoItem;
	QGraphicsTextItem *subTextItem;
	QGraphicsScene *scene;
	QMediaPlayer *player;
	qreal subTextScaleFactor = 1.0;
	qreal mediaSeekFactor = 250;

	void SetupButtonIcons();
	void SetupVideoWidget();
	void SetupSubtitlesTable();
	void ConnectEvents();

	void SetMediaControlsEnabled(bool isEnabled);

	void UpdateUI();
	void UpdateSubAlignment();
	void UpdateSubPosition();

	QTime MsToTime(int ms);

	void SetWindowTitle(const QString title);
	bool CheckIfSaved();
	void SetIsSaved(bool value);

	void ShowAvailableSub();

private slots:
	// File Menu
	void NewAction();
	void OpenAction();
	void SaveAction();
	void SaveAsAction();
	void CloseAction();
	void ExitAction();

	// Edit Menu
	void UndoAction();
	void RedoAction();
	void GotoPreviousSub();
	void GotoNextSub();
	void DelaySubtitles();

	// Media Menu
	void OpenMediaAction();
	void CloseMediaAction();

	// Help Menu
	void AboutHelpAction();
	void AboutQtHelpAction();

	// Media
	void OpenMediaFile(const QString &Path);

	void VideoSeekableChanged(bool value);
	void VideoDurationChanged(qint64 value);
	void VideoPositionChanged(qint64 value);

	void TimelineSliderChanged(int value);
	void TogglePlayVideo();
	void StopVideo();
	void SeekForwards();
	void SeekBackwards();
	void VolumeUp();
	void VolumeDown();
	void ToggleMuteAudio();
	void VolumeSliderChanged(int value);

	// Subtitle Group
	void OpenSubtitleFile(const QString &Path);

	void DisplaySubtitle(const SubtitleItem &subItem);
	void ClearSubtitle();

	void SelectSubFromTable(int row);

	void SubTableRowClicked(QModelIndex index);

	void SubShowTimeChanged();
	void SubHideTimeChanged();
	void SubDurationChanged();

	void SubTextChanged();
	void SubCursorPosChanged();

	void SubBoldClicked();
	void SubItalicClicked();
	void SubUnderlineClicked();
	void SubStrikeoutClicked();

	void SubTextToggleTag(const QString &tag);

	void ApplySubtitlePressed();
	void RemoveSubtitle();

	bool ApplySubtitle(const SubtitleItem &item, const int index);
	bool ApplySubtitles(const QList<SubtitleItem> &items);
};
