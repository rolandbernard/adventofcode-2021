
Object subclass: #BingoGame
	instanceVariableNames: 'numbers boards numberDictionary'
	classVariableNames: ''
	package: 'AAA'!

!BingoGame methodsFor: 'running' stamp: 'RolandBernard 12/5/2021 14:23'!
winningBoardScore

	| min board |
	min := Float infinity.
	board := nil.
	boards do: [ :b | 
		| count |
		count := b winTime: self numberDictionary.
		count < min ifTrue: [ 
			min := count.
			board := b ] ].
	^ board scoreAt: min for: self numberDictionary! !

!BingoGame methodsFor: 'running' stamp: 'RolandBernard 12/5/2021 14:23'!
losingBoardScore

	| max board |
	max := Float infinity negated.
	board := nil.
	boards do: [ :b | 
		| count |
		count := b winTime: self numberDictionary.
		count > max ifTrue: [ 
			max := count.
			board := b ] ].
	^ board scoreAt: max for: self numberDictionary! !


!BingoGame methodsFor: 'accessing' stamp: 'RolandBernard 12/5/2021 00:05'!
numbers: anObject
	numberDictionary := nil.
	numbers := anObject! !

!BingoGame methodsFor: 'accessing' stamp: 'RolandBernard 12/5/2021 14:32'!
numberDictionary

	^ numberDictionary ifNil: [ 
		  numberDictionary := (numbers collectWithIndex: [ :e :i | e -> i ])
			                      asDictionary ]! !

!BingoGame methodsFor: 'accessing' stamp: 'RolandBernard 12/4/2021 23:50'!
boards: anObject

	boards := anObject! !

"-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- "!

BingoGame class
	instanceVariableNames: ''!

!BingoGame class methodsFor: 'instance creation' stamp: 'RolandBernard 12/5/2021 14:20'!
loadFromFile: aFilename

	| text split numbers boards |
	text := aFilename asFileReference contents.
	split := text splitOn: String lf , String lf.
	numbers := (split first splitOn: ',') collect: [ :e | e asNumber ].
	boards := (2 to: split size) collect: [ :i | 
		          Board forValues:
			          ((((split at: i) splitOn: String lf) reject: [ :e | 
				            e isEmpty ]) collect: [ :l | 
				           ((l splitOn: ' ') reject: [ :e | e isEmpty ]) collect: [ 
					           :e | e asNumber ] ]) ].
	^ self forNumbers: numbers  boards: boards! !

!BingoGame class methodsFor: 'instance creation' stamp: 'RolandBernard 12/5/2021 14:21'!
loadFromFile

	^ self loadFromFile: (Smalltalk ui theme
			 chooseFileIn: self currentWorld
			 title: 'Choose a file'
			 extensions: nil
			 path: nil
			 preview: true) fullName! !

!BingoGame class methodsFor: 'instance creation' stamp: 'RolandBernard 12/4/2021 23:53'!
forNumbers: aCollection boards: bCollection

	^ self new
		  numbers: aCollection;
		  boards: bCollection;
		  yourself! !
